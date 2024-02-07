#include <engine/Engine.hpp>





using namespace engine::render;
using namespace engine::modules::ui;

namespace engine
{
	auto Engine::setApplicationRenderer(render_ptr_t _renderer) noexcept -> void
	{
		application_renderer::instance().setupRenderer(std::move(_renderer));
	}



	auto Engine::setApplicationUIModule(UIModule_ptr_t _UI_module) noexcept -> void
	{
		application_UIModule::instance().setupUIModule(std::move(_UI_module));
	}



	auto Engine::setCommonExecutionThreadsCount(size_t _threads_count) noexcept -> void
	{
		application_executor::setCommonThreadsCount(_threads_count);
	}



	auto Engine::setThreadsCountForAsyncExecution(size_t _threads_count) noexcept -> void
	{
		application_executor::setThreadsCountForAsyncExecution(_threads_count);
	}



	auto Engine::getApplicationRenderer() noexcept -> const render_ptr_t&
	{
		return application_renderer::instance().getRenderer();
	}



	auto Engine::getApplicationUIModule() noexcept -> const UIModule_ptr_t&
	{
		return application_UIModule::instance().getUIModule();
	}



	auto Engine::getApplicationExecutor() noexcept -> const application_executor_ptr_t&
	{
		return application_executor::instance();
	}
}