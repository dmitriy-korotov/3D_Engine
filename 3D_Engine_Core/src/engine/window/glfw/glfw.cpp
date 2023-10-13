#include <engine/window/glfw/glfw.hpp>

#include <engine/util/image.hpp>

#include <engine/logging/log.hpp>

#include <GLFW/glfw3.h>

#include <iostream>



namespace engine::window::glfw
{
	static constexpr int windowHintToGlfwHint(WindowHint _hint) noexcept
	{
		switch (_hint)
		{
		case engine::window::glfw::WindowHint::RedBits:			return GLFW_RED_BITS;
		case engine::window::glfw::WindowHint::GreenBits:		return GLFW_GREEN_BITS;
		case engine::window::glfw::WindowHint::BlueBits:		return GLFW_BLUE_BITS;
		case engine::window::glfw::WindowHint::RefreshRate:		return GLFW_REFRESH_RATE;
		}
		LOG_ERROR("[Glfw ERROR] Window hint is not found (code: {0}).", static_cast<int>(_hint));

		return GLFW_RED_BITS;
	}





	monitor::monitor(GLFWmonitor* _monitor) noexcept
			: m_monitor_ptr(_monitor)
	{ }



	video_mode::video_mode(const GLFWvidmode* _video_mode) noexcept
			: m_video_mode_ptr(_video_mode)
	{ }



	int video_mode::redBits() const noexcept		{ return m_video_mode_ptr->redBits; }
	int video_mode::greenBits() const noexcept		{ return m_video_mode_ptr->greenBits; }
	int video_mode::blueBits() const noexcept		{ return m_video_mode_ptr->blueBits; }
	int video_mode::refreshRate() const noexcept	{ return m_video_mode_ptr->refreshRate; }

	uint16_t video_mode::width() const noexcept		{ return m_video_mode_ptr->width; };
	uint16_t video_mode::height() const noexcept	{ return m_video_mode_ptr->height; };





	glfw& glfw::instance() noexcept
	{
		static glfw instance;
		return instance;
	}



	void glfw::init() noexcept
	{
		if (!m_is_inited)
		{
			if (!glfwInit())
				LOG_CRITICAL("[Glfw ERROR] Can't initializate glfw.");
			
			glfwSetErrorCallback(
				[](int _error_code, const char* _description) -> void
				{
					LOG_ERROR("[Glfw ERROR] (code: {0}): {1}", _error_code, _description);
				});
			m_is_inited = true;
		}
	}



	void glfw::getCurrentCursorPosition(GLFWwindow* _window_ptr, double& _x, double& _y) const noexcept
	{
		glfwGetCursorPos(_window_ptr, &_x, &_y);
	}



	void glfw::setWindowIcon(GLFWwindow* _window_ptr, util::image& _icon) const noexcept
	{
		GLFWimage glfw_icon;
		glfw_icon.pixels = reinterpret_cast<unsigned char*>(_icon.getData());
		glfw_icon.height = _icon.getHeight();
		glfw_icon.width = _icon.getWidth();
		glfwSetWindowIcon(_window_ptr, 1, &glfw_icon);
	}



	void glfw::pollEvents() const noexcept
	{
		glfwPollEvents();
	}



	void glfw::makeContextCurrent(GLFWwindow* _window_ptr) const noexcept
	{
		glfwMakeContextCurrent(_window_ptr);
	}



	void glfw::swapBuffers(GLFWwindow* _window_ptr) const noexcept
	{
		glfwSwapBuffers(_window_ptr);
	}



	monitor glfw::getPrimaryMonitor() const noexcept
	{
		return monitor(glfwGetPrimaryMonitor());
	}



	video_mode glfw::getVideoMode(const monitor& _monitor) const noexcept
	{
		return video_mode(glfwGetVideoMode(_monitor.m_monitor_ptr));
	}



	void glfw::windowHint(WindowHint _hint, int _value) const noexcept
	{
		glfwWindowHint(windowHintToGlfwHint(_hint), _value);
	}



	GLFWwindow* glfw::createWindow(uint16_t _width, uint16_t _height, const std::string_view& _title,
								   const monitor& _monitor, GLFWwindow* _share) const noexcept
	{
		return glfwCreateWindow(_width, _height, _title.data(), _monitor.m_monitor_ptr, _share);
	}



	void glfw::setWindowResizeCallBack(GLFWwindow* _window_ptr, GLFWwindowsizefun _call_back) const noexcept
	{
		glfwSetWindowSizeCallback(_window_ptr, _call_back);
	}



	void glfw::setWindowCloseCallBack(GLFWwindow* _window_ptr, GLFWwindowclosefun _call_back) const noexcept
	{
		glfwSetWindowCloseCallback(_window_ptr, _call_back);
	}



	void glfw::setKeyCallback(GLFWwindow* _window_ptr, GLFWkeyfun _call_back) const noexcept
	{
		glfwSetKeyCallback(_window_ptr, _call_back);
	}



	void glfw::setMouseButtonCallback(GLFWwindow* _window_ptr, GLFWmousebuttonfun _call_back) const noexcept
	{
		glfwSetMouseButtonCallback(_window_ptr, _call_back);
	}



	void glfw::setCursorPosCallback(GLFWwindow* _window_ptr, GLFWcursorposfun _call_back) const noexcept
	{
		glfwSetCursorPosCallback(_window_ptr, _call_back);
	}



	void glfw::destroyWindow(GLFWwindow* _window_ptr) const noexcept
	{
		glfwDestroyWindow(_window_ptr);
	}



	bool glfw::isInited() const noexcept
	{
		return m_is_inited;
	}



	void glfw::terminate() noexcept
	{
		glfwTerminate();
		m_is_inited = false;
	}
}