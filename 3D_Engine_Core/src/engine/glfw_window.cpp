#include <engine/window/glfw_window.hpp>

#include <engine/error.hpp>
#include <engine/logging/log.hpp>

#include <GLFW/glfw3.h>



static bool s_glfw_ininted = false;



namespace engine
{
	std::vector<glfw_window*> glfw_window::s_all_windows_;





	glfw_window::glfw_window(std::uint16_t _width, std::uint16_t _height,
							 const std::string_view& _title)
			: basic_window(_width, _height, _title)
	{
		if (create().has_value())
		{
			LOG_CRITICAL("Can't create window '{0}' with size {1}x{2}.", m_window_data.title, m_window_data.width, m_window_data.height);
			throw std::exception("Window not inited.");
		};
		s_all_windows_.push_back(this);
	}



	const GLFWwindow* glfw_window::__getRawPtr() const noexcept
	{
		return m_window_ptr;
	}



	void glfw_window::onUpdate() noexcept
	{
		glfwSwapBuffers(m_window_ptr);
		glfwPollEvents();
	}



	std::optional<error::window_error> glfw_window::__glfwInit() const noexcept
	{
		if (!s_glfw_ininted)
		{
			if (!glfwInit())
			{
				LOG_CRITICAL("Can't initializate glfw.");
				return error::window_error::can_not_create;
			}
			s_glfw_ininted = true;
		}
		return std::nullopt;
	}



	std::optional<error::window_error> glfw_window::create() noexcept
	{
		auto result_ = __glfwInit();
		if (result_.has_value())
		{
			return result_;
		}

		m_window_ptr = glfwCreateWindow(m_window_data.width, m_window_data.height, m_window_data.title.c_str(), nullptr, nullptr);
		if (!m_window_ptr)
		{
			LOG_CRITICAL("Can't create window.");
			glfwTerminate();
			return error::window_error::can_not_create;
		}
		glfwMakeContextCurrent(m_window_ptr);

		return std::nullopt;
	}



	void glfw_window::shutdown() noexcept
	{
		glfwDestroyWindow(m_window_ptr);
		glfwTerminate();
	}



	glfw_window::~glfw_window()
	{
		shutdown();
	}









	glfw_window* getWindow(GLFWwindow* _window_ptr)
	{
		for (auto window_ : glfw_window::s_all_windows_)
		{
			if (window_->__getRawPtr() == _window_ptr)
			{
				return window_;
			}
		}
	}



	std::pair<glfw_window::WindowData&, const window::CallBackStorage&> __getWindowDataAndCallBackStorage(glfw_window& _window) noexcept
	{
		return std::make_pair(std::ref(_window.m_window_data), std::cref(_window.m_window_call_backs_));
	}
}