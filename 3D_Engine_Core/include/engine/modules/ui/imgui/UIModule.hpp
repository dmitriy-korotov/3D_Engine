#pragma once

#include <engine/modules/ui/basic_UIModule.hpp>



namespace engine::modules::ui::imgui
{
	class UIModule: public basic_UIModule
	{
	public:

		static UIModule& instance() noexcept;

		void initialize(const window_ptr& _window_ptr) noexcept override;
		void terminate() noexcept override;

		void onUIDrawBegin() const noexcept override;
		void onUIDrawEnd() const noexcept override;

		bool isMouseOnUI() const noexcept override;

		void createDockSpace() const noexcept override;

	private:

		void setupImGuiConfig() const noexcept;

	};
}