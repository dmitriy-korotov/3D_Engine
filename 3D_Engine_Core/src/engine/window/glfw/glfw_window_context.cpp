#include <engine/window/glfw/glfw_window_context.hpp>

#include <engine/window/glfw/glfw.hpp>
#include <engine/window/glfw/glfw_window.hpp>



namespace engine::window::glfw
{
	void glfw_window_context::init() const noexcept
	{
		glfw::instance().init();
	}



	void glfw_window_context::terminate() const noexcept
	{
		glfw::instance().terminate();
	}



	std::shared_ptr<basic_window> glfw_window_context::createWindow() const noexcept
	{
		return std::make_shared<glfw_window>();
	}
}