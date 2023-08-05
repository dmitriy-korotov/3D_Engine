#pragma once

#include <engine/window/basic_window.hpp>
#include <engine/window/event_structs.hpp>



struct GLFWwindow;

namespace engine
{
	class glfw_window final : public basic_window
	{
	public:

		glfw_window(std::uint16_t _width, std::uint16_t _height,
					const std::string_view& _title);
		~glfw_window();

		void onUpdate() noexcept override;

		template<>

	private:

		std::optional<error::window_error> create() noexcept override;
		void shutdown() noexcept override;
		
		std::optional<error::window_error> __glfwInit() const noexcept;

	private:

		GLFWwindow* m_window_ptr = nullptr;

	};
}