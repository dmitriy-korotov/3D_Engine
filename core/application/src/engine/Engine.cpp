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



	auto Engine::getApplicationRenderer() noexcept -> const render_ptr_t&
	{
		return application_renderer::instance().getRenderer();
	}



	auto Engine::getApplicationUIModule() noexcept -> const UIModule_ptr_t&
	{
		return application_UIModule::instance().getUIModule();
	}
}