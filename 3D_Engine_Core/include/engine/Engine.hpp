#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/render/application_renderer.hpp>
#include <engine/modules/ui/application_UIModule.hpp>



namespace engine
{
	class Engine: private util::noconstructible
	{
	public:

		using render_ptr = render::application_renderer::renderer_ptr;
		using UIModule_ptr = modules::ui::application_UIModule::UIModule_ptr;

		static void setApplicationRenderer(render_ptr _renderer) noexcept;
		static void setApplicationUIModule(UIModule_ptr _UI_module) noexcept;

		static const render_ptr& getApplicationRenderer() noexcept;
		static const UIModule_ptr& getApplicationUIModule() noexcept;

	};
}