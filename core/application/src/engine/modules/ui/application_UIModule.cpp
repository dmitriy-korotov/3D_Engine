#include <engine/modules/ui/application_UIModule.hpp>

#include <engine/modules/ui/basic_UIModule.hpp>

#include <cassert>



namespace engine::modules::ui
{
	auto application_UIModule::instance() noexcept -> application_UIModule&
	{
		static application_UIModule instance;
		return instance;
	}



	auto application_UIModule::setupUIModule(UIModule_ptr_t _UI_module) noexcept -> void
	{
		m_UI_module = std::move(_UI_module);
	}



	auto application_UIModule::getUIModule() const noexcept -> const UIModule_ptr_t&
	{
		assert(m_UI_module != nullptr);
		return m_UI_module;
	}
}