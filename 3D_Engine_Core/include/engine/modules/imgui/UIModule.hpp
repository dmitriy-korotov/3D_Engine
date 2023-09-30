#pragma once

#include <engine/modules/basic_UIModule.hpp>



namespace engine::modules::imgui
{
	class UIModule: public basic_UIModule
	{
	public:

		static UIModule& instance() noexcept;

		void onWindowCreate(const window_ptr& _window_ptr) const noexcept override;
		void onWindowShutdown() const noexcept override;
		void onUIDrawBegin() const noexcept override;
		void onUIDrawEnd() const noexcept override;

		void createDockSpace() const noexcept override;

	private:

		void setupImGuiConfig() const noexcept;

	};
}