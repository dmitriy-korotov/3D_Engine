#include <engine/Engine.hpp>



namespace engine
{
	void Engine::setApplicationRenderer(render_ptr _renderer) noexcept
	{
		render::application_renderer::instance().setupRenderer(std::move(_renderer));
	}



	void Engine::setApplicationUIModule(UIModule_ptr _UI_module) noexcept
	{
		modules::application_UIModule::instance().setUIModule(std::move(_UI_module));
	}



	const Engine::render_ptr& Engine::getApplicationRenderer() noexcept
	{
		return render::application_renderer::instance().getRenderer();
	}



	const Engine::UIModule_ptr& Engine::getApplicationUIModule() noexcept
	{
		return modules::application_UIModule::instance().getUIModule();
	}
}