#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/render/application_renderer.hpp>
#include <engine/modules/ui/application_UIModule.hpp>
#include <engine/application_executor.hpp>



namespace engine
{
	class Engine: private util::noconstructible
	{
	public:

		using render_ptr_t = render::application_renderer::renderer_ptr_t;
		using UIModule_ptr_t = modules::ui::application_UIModule::UIModule_ptr_t;
		using application_executor_ptr_t = application_executor::application_executor_ptr_t;

		static void setApplicationRenderer(render_ptr_t _renderer) noexcept;
		static void setApplicationUIModule(UIModule_ptr_t _UI_module) noexcept;
		static void setCommonExecutionThreadsCount(size_t _threads_count) noexcept;
		static void setThreadsCountForAsyncExecution(size_t _threads_count) noexcept;

		static const render_ptr_t& getApplicationRenderer() noexcept;
		static const UIModule_ptr_t& getApplicationUIModule() noexcept;
		static const application_executor_ptr_t& getApplicationExecutor() noexcept;

	};
}