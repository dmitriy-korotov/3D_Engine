#pragma once

#include <engine/util/nocopyeble.hpp>

#include <memory>



namespace engine::modules
{
	class basic_UIModule;

	class application_UIModule: private util::nocopyeble
	{
	public:

		using UIModule_ptr = std::shared_ptr<basic_UIModule>;

		static application_UIModule& instance() noexcept;

		void setUIModule(UIModule_ptr _UI_module) noexcept;

		const UIModule_ptr& getUIModule() const noexcept;

	private:

		application_UIModule() = default;

	private:

		UIModule_ptr m_UI_module = nullptr;

	};
}