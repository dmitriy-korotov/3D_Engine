#include <engine/Engine.hpp>



using namespace engine::render;
using namespace engine::modules;

namespace engine
{
	void Engine::setApplicationRenderer(render_ptr _renderer) noexcept
	{
		application_renderer::instance().setupRenderer(std::move(_renderer));
	}



	void Engine::setApplicationUIModule(UIModule_ptr _UI_module) noexcept
	{
		application_UIModule::instance().setUIModule(std::move(_UI_module));
	}



	const Engine::render_ptr& Engine::getApplicationRenderer() noexcept
	{
		return application_renderer::instance().getRenderer();
	}



	const Engine::UIModule_ptr& Engine::getApplicationUIModule() noexcept
	{
		return application_UIModule::instance().getUIModule();
	}
}