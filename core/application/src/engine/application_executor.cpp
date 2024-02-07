#include <engine/application_executor.hpp>

#include <engine/logging/log.hpp>

#include <thread>



namespace engine
{
	size_t application_executor::m_common_threads_count = std::thread::hardware_concurrency();
	size_t application_executor::m_threads_count_for_async_execution = 1;
	application_executor::application_executor_ptr_t application_executor::m_executor_ptr = nullptr;





	auto application_executor::setCommonThreadsCount(size_t _threads_count) noexcept -> void
	{
		if (m_executor_ptr != nullptr)
			LOG_WARN("[Application executor WARN] Executor already created, "
					 "please set threads count before call 'getApplicationExecutor' method");
		m_common_threads_count = _threads_count;
	}



	auto application_executor::setThreadsCountForAsyncExecution(size_t _threads_count_for_async_exec) noexcept -> void
	{
		if (_threads_count_for_async_exec > m_common_threads_count)
		{
			LOG_WARN("[Application executor WARN] Common excution threads '{0}' "
					 "must be greater then threads for async execution '{1}'", m_common_threads_count, _threads_count_for_async_exec);
			return;
		}
		m_threads_count_for_async_execution = _threads_count_for_async_exec;
	}



	auto application_executor::getCommonThreadsCount() noexcept -> size_t
	{
		return m_common_threads_count;
	}



	auto application_executor::getThreadsCountForAsyncExecution() noexcept -> size_t
	{
		return m_threads_count_for_async_execution;
	}



	auto application_executor::instance() -> const application_executor_ptr_t&
	{
		if (m_executor_ptr == nullptr)
			m_executor_ptr = std::unique_ptr<application_executor>(new application_executor(m_common_threads_count));
		return m_executor_ptr;
	}



	application_executor::application_executor(size_t _threads_count) noexcept
			: m_pool(_threads_count)
			, m_signals_set(m_io_context, SIGTERM, SIGABRT, SIGINT)
	{ }



	auto application_executor::initExecutionContext() noexcept -> void
	{
		m_signals_set.async_wait(
			[this](asio::error_code _error, int _signal_code) -> void
			{
				signalsHandler(_error, _signal_code);
			});

		for (ptrdiff_t i = 0; i < m_threads_count_for_async_execution; i++)
			createNewThreadForAsyncExecution();
	}



	auto application_executor::waitCompletionAllTasks() noexcept -> void
	{
		m_pool.join();
	}



	auto application_executor::stopAllExecutions() noexcept -> void
	{
		m_io_context.stop();
		m_pool.stop();
	}



	auto application_executor::IOContext() noexcept -> asio::io_context&
	{
		return m_io_context;
	}



	auto application_executor::createNewThreadForAsyncExecution() noexcept -> void
	{
		asio::post(m_pool,
			[this]() -> void
			{
				try
				{
					m_io_context.run();
				}
				catch (const std::exception& _ex)
				{
					LOG_CRITICAL("[Application executor CRITICAL] IO context exception: '{0}'", std::string(_ex.what()));
				}
			});
	}



	auto application_executor::signalsHandler(asio::error_code _error, int _signal_code) noexcept -> void
	{
		if (_error)
		{
			LOG_ERROR("[Application executor ERROR] Error on signal with code '{0}': '{1}'", _signal_code, _error.message());
			return;
		}
		stopAllExecutions();
	}
}