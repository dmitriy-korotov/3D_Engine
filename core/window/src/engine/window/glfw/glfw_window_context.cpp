#include <engine/window/glfw/glfw_window_context.hpp>

#include <engine/window/glfw/glfw.hpp>
#include <engine/window/glfw/glfw_window.hpp>



namespace engine::window::glfw
{
	auto glfw_window_context::init() const noexcept -> void
	{
		glfw::instance().init();
	}



	auto glfw_window_context::terminate() const noexcept -> void
	{
		glfw::instance().terminate();
	}



	auto glfw_window_context::createWindow() const noexcept -> window_sptr_t
	{
		return std::make_shared<glfw_window>();
	}
}