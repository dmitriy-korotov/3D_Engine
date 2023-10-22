#include <engine/Engine.hpp>





using namespace engine::render;
using namespace engine::modules::ui;

namespace engine
{
	void Engine::setApplicationRenderer(render_ptr_t _renderer) noexcept
	{
		application_renderer::instance().setupRenderer(std::move(_renderer));
	}



	void Engine::setApplicationUIModule(UIModule_ptr_t _UI_module) noexcept
	{
		application_UIModule::instance().setUIModule(std::move(_UI_module));
	}



	const Engine::render_ptr_t& Engine::getApplicationRenderer() noexcept
	{
		return application_renderer::instance().getRenderer();
	}



	const Engine::UIModule_ptr_t& Engine::getApplicationUIModule() noexcept
	{
		return application_UIModule::instance().getUIModule();
	}
}