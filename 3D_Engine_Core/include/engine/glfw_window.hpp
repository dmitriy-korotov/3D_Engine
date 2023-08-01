#pragma once

#include <engine/basic_window.hpp>



struct GLFWwindow;

namespace engine
{
	class glfw_window final : public basic_window
	{
	public:

		glfw_window(std::uint16_t _width, std::uint16_t _height,
					const std::string_view& _title);

		void onUpdate() noexcept override;
		bool isShouldClose() const noexcept override;

	private:

		std::optional<error::window_error> create() noexcept override;
		void shutdown() noexcept override;
		
		std::optional<error::window_error> glfwInit() const noexcept;

	private:

		GLFWwindow* m_window_ptr = nullptr;

	};
}