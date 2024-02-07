#pragma once

#define _WIN32_WINNT 0x0601

#include <engine/util/nocopyeble.hpp>
#include <engine/util/concepts.hpp>

#include <asio/static_thread_pool.hpp>
#include <asio/io_context.hpp>
#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/signal_set.hpp>

#include <functional>
#include <memory>
#include <concepts>



namespace engine
{
	struct unit_t {};

	class application_executor : public util::nocopyeble
	{
	public:

		template <typename Task, typename ...Args>
		requires std::invocable<Task&&, Args&&...>
		class execution_chain;

		using application_executor_ptr_t = std::unique_ptr<application_executor>;



		static void setCommonThreadsCount(size_t _threads_count) noexcept;
		static void setThreadsCountForAsyncExecution(size_t _threads_count_for_async_exec) noexcept;
		static size_t getCommonThreadsCount() noexcept;
		static size_t getThreadsCountForAsyncExecution() noexcept;
		
		
		
		static const application_executor_ptr_t& instance();



		void initExecutionContext() noexcept;
		void waitCompletionAllTasks() noexcept;

		void stopAllExecutions() noexcept;

		asio::io_context& IOContext() noexcept;

		template <typename Task, typename ...Args>
		requires std::invocable<Task&&, Args&&...>
		void completeTaskConcurrent(Task&& _task, Args&& ..._args) noexcept;

		template <typename Task, typename ...Args>
		requires std::invocable<Task&&, Args&&...>
		decltype(auto) completeTaskBlocking(Task&& _task, Args&& ..._args) noexcept;

		template <typename Task, typename ...Args>
		requires std::invocable<Task&&, Args&&...> && util::is_awaitable<std::invoke_result_t<Task&&, Args&&...>>
		auto completeTaskAsync(Task&& _task, Args&& ..._args) noexcept;

	private:

		template <typename Task, typename ...Args>
		requires std::invocable<Task&&, Args&&...>
		class execution_chain
		{
		public:

			using ret_type = std::invoke_result_t<Task&&, Args&&...>;



			execution_chain(asio::io_context& _execution_context, Task&& _task, Args&& ..._args) noexcept;
			~execution_chain();

			template <typename Handler>
			requires std::invocable<Handler&&, typename std::invoke_result_t<Task&&, Args&&...>::value_type>
			auto then(Handler&& _handler) && noexcept;

			void end() && noexcept;

		private:

			bool m_is_ended = false;
			asio::io_context& m_execution_context;
			std::function<ret_type()> m_task;

		};

	private:

		application_executor(size_t _threads_count) noexcept;

		void createNewThreadForAsyncExecution() noexcept;
		void signalsHandler(asio::error_code _error, int _signal_code) noexcept;

	private:

		static size_t m_common_threads_count;
		static size_t m_threads_count_for_async_execution;
		static application_executor_ptr_t m_executor_ptr;

	private:

		asio::io_context m_io_context;
		asio::signal_set m_signals_set;
		asio::static_thread_pool m_pool;

	};





	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...>
	inline auto application_executor::completeTaskConcurrent(Task&& _task, Args&& ..._args) noexcept -> void
	{
		asio::post(m_pool, std::bind(std::forward<Task>(_task), std::forward<Args>(_args)...));
	}



	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...>
	inline auto application_executor::completeTaskBlocking(Task&& _task, Args&& ..._args) noexcept -> decltype(auto)
	{
		return std::invoke(std::forward<Task>(_task), std::forward<Args>(_args)...);
	}



	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...> && util::is_awaitable<std::invoke_result_t<Task&&, Args&&...>>
	inline auto application_executor::completeTaskAsync(Task&& _task, Args&& ..._args) noexcept
	{
		return execution_chain<Task, Args...>(m_io_context, std::forward<Task>(_task), std::forward<Args>(_args)...);
	}





	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...>
	application_executor::execution_chain<Task, Args...>::execution_chain(
		asio::io_context& _execution_context,
		Task&& _task,
		Args&& ..._args
	) noexcept
		: m_execution_context(_execution_context)
		, m_task(std::bind(std::forward<Task>(_task), std::forward<Args>(_args)...))
	{ }



	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...>
	application_executor::execution_chain<Task, Args...>::~execution_chain()
	{
		if (!m_is_ended)
			std::move(*this).end();
	}



	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...>
	template <typename Handler>
	requires std::invocable<Handler&&, typename std::invoke_result_t<Task&&, Args&&...>::value_type>
	inline auto application_executor::execution_chain<Task, Args...>::then(Handler&& _handler) && noexcept
	{
		using handler_ret_type = std::invoke_result_t<Handler&&, typename ret_type::value_type&&>;
		using BindedTask_t = decltype(m_task);

		m_is_ended = true;

		auto wrapper =
			+[](BindedTask_t _binded_task, Handler _handler) -> asio::awaitable<handler_ret_type>
			{
				typename ret_type::value_type result = co_await std::invoke(std::move(_binded_task));
				co_return std::invoke(std::forward<Handler>(_handler), std::move(result));
			};

		return execution_chain<decltype(std::move(wrapper)),
							   BindedTask_t&&,
							   Handler&&>(m_execution_context,
									  	  std::move(wrapper),
										  std::move(m_task),
										  std::forward<Handler>(_handler));
	}



	template <typename Task, typename ...Args>
	requires std::invocable<Task&&, Args&&...>
	inline auto application_executor::execution_chain<Task, Args...>::end() && noexcept -> void
	{
		using BindedTask_t = decltype(m_task);

		auto wrapper =
			+[](BindedTask_t _binded_task) -> std::invoke_result_t<BindedTask_t&&>
			{
				co_return co_await std::invoke(std::move(_binded_task));
			};

		asio::co_spawn(m_execution_context.get_executor(),
					   wrapper(std::move(m_task)),
					   asio::detached);

		m_is_ended = true;
	}
}