#include <engine/modules/ui/application_UIModule.hpp>

#include <engine/modules/ui/basic_UIModule.hpp>

#include <cassert>



namespace engine::modules::ui
{
	application_UIModule& application_UIModule::instance() noexcept
	{
		static application_UIModule instance;
		return instance;
	}



	void application_UIModule::setUIModule(UIModule_ptr _UI_module) noexcept
	{
		m_UI_module = std::move(_UI_module);
	}



	const application_UIModule::UIModule_ptr& application_UIModule::getUIModule() const noexcept
	{
		assert(m_UI_module != nullptr);
		return m_UI_module;
	}
}