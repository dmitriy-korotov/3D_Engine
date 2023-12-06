#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/modules/ui/basic_UIModule.hpp>

#include <memory>



namespace engine::modules::ui
{
	class application_UIModule: private util::nocopyeble
	{
	public:

		using UIModule_ptr_t = std::shared_ptr<basic_UIModule>;

		static application_UIModule& instance() noexcept;

		void setupUIModule(UIModule_ptr_t _UI_module) noexcept;
		const UIModule_ptr_t& getUIModule() const noexcept;

	private:

		application_UIModule() = default;

	private:

		UIModule_ptr_t m_UI_module = nullptr;

	};
}