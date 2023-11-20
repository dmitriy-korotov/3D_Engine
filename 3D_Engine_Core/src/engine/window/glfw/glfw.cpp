#include <engine/window/glfw/glfw.hpp>

#include <engine/util/image.hpp>

#include <engine/logging/log.hpp>

#include <GLFW/glfw3.h>



namespace engine::window::glfw
{
	static constexpr auto windowHintToGlfwHint(WindowHint _hint) noexcept -> int
	{
		switch (_hint)
		{
		case WindowHint::RedBits:			return GLFW_RED_BITS;
		case WindowHint::GreenBits:			return GLFW_GREEN_BITS;
		case WindowHint::BlueBits:			return GLFW_BLUE_BITS;
		case WindowHint::RefreshRate:		return GLFW_REFRESH_RATE;
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



	auto video_mode::redBits() const noexcept -> int			{ return m_video_mode_ptr->redBits; }
	auto video_mode::greenBits() const noexcept -> int			{ return m_video_mode_ptr->greenBits; }
	auto video_mode::blueBits() const noexcept -> int			{ return m_video_mode_ptr->blueBits; }
	auto video_mode::refreshRate() const noexcept -> int		{ return m_video_mode_ptr->refreshRate; }

	auto video_mode::width() const noexcept -> uint16_t			{ return m_video_mode_ptr->width; };
	auto video_mode::height() const noexcept -> uint16_t		{ return m_video_mode_ptr->height; };





	auto glfw::instance() noexcept -> glfw&
	{
		static glfw instance;
		return instance;
	}



	auto glfw::init() noexcept -> void
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



	auto glfw::getCurrentCursorPosition(GLFWwindow* _window_ptr, double& _x, double& _y) const noexcept -> void
	{
		glfwGetCursorPos(_window_ptr, &_x, &_y);
	}



	auto glfw::setWindowIcon(GLFWwindow* _window_ptr, util::image& _icon) const noexcept -> void
	{
		GLFWimage glfw_icon;
		glfw_icon.pixels = reinterpret_cast<unsigned char*>(_icon.getData());
		glfw_icon.height = _icon.getHeight();
		glfw_icon.width = _icon.getWidth();
		glfwSetWindowIcon(_window_ptr, 1, &glfw_icon);
	}



	auto glfw::pollEvents() const noexcept -> void
	{
		glfwPollEvents();
	}



	auto glfw::makeContextCurrent(GLFWwindow* _window_ptr) const noexcept -> void
	{
		glfwMakeContextCurrent(_window_ptr);
	}



	auto glfw::swapBuffers(GLFWwindow* _window_ptr) const noexcept -> void
	{
		glfwSwapBuffers(_window_ptr);
	}



	auto glfw::getPrimaryMonitor() const noexcept -> monitor
	{
		return monitor(glfwGetPrimaryMonitor());
	}



	auto glfw::getVideoMode(const monitor& _monitor) const noexcept -> video_mode
	{
		return video_mode(glfwGetVideoMode(_monitor.m_monitor_ptr));
	}



	auto glfw::windowHint(WindowHint _hint, int _value) const noexcept -> void
	{
		glfwWindowHint(windowHintToGlfwHint(_hint), _value);
	}



	auto glfw::createWindow(uint16_t _width, uint16_t _height, const std::string_view& _title,
								   const monitor& _monitor, GLFWwindow* _share) const noexcept -> GLFWwindow*
	{
		return glfwCreateWindow(_width, _height, _title.data(), _monitor.m_monitor_ptr, _share);
	}



	auto glfw::setWindowResizeCallBack(GLFWwindow* _window_ptr, GLFWwindowsizefun _call_back) const noexcept -> void
	{
		glfwSetWindowSizeCallback(_window_ptr, _call_back);
	}



	auto glfw::setWindowCloseCallBack(GLFWwindow* _window_ptr, GLFWwindowclosefun _call_back) const noexcept -> void
	{
		glfwSetWindowCloseCallback(_window_ptr, _call_back);
	}



	auto glfw::setKeyCallback(GLFWwindow* _window_ptr, GLFWkeyfun _call_back) const noexcept -> void
	{
		glfwSetKeyCallback(_window_ptr, _call_back);
	}



	auto glfw::setMouseButtonCallback(GLFWwindow* _window_ptr, GLFWmousebuttonfun _call_back) const noexcept -> void
	{
		glfwSetMouseButtonCallback(_window_ptr, _call_back);
	}



	auto glfw::setCursorPosCallback(GLFWwindow* _window_ptr, GLFWcursorposfun _call_back) const noexcept -> void
	{
		glfwSetCursorPosCallback(_window_ptr, _call_back);
	}



	auto glfw::destroyWindow(GLFWwindow* _window_ptr) const noexcept -> void
	{
		glfwDestroyWindow(_window_ptr);
	}



	auto glfw::isInited() const noexcept -> bool
	{
		return m_is_inited;
	}



	auto glfw::terminate() noexcept -> void
	{
		glfwTerminate();
		m_is_inited = false;
	}
}