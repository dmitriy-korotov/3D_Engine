#pragma once

#include <engine/window/basic_window_context.hpp>



namespace engine::window::glfw
{
	class glfw_window_context: public basic_window_context
	{
	public:

		void init() const noexcept override;
		void terminate() const noexcept override;

		[[nodiscard]] virtual std::shared_ptr<basic_window> createWindow() const noexcept override;

	};
}