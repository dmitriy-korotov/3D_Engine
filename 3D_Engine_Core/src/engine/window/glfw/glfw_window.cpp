#include <engine/window/glfw/glfw_window.hpp>

#include <engine/error/window_error.hpp>
#include <engine/logging/log.hpp>

#include <engine/window/glfw/windows_manager.hpp>

#include <GLFW/glfw3.h>



namespace engine::window::glfw
{
	window::window(const std::string_view& _title)
			: basic_window(_title)
	{ }



	void window::onUpdate() noexcept
	{
		glfwSwapBuffers(m_window_ptr);
		glfwPollEvents();
	}



	std::optional<error::window_error> window::__glfwInit() const noexcept
	{
		if (!glfwInit())
		{
			LOG_CRITICAL("[Glfw Window ERROR] Can't initializate glfw.");
			return error::window_error::can_not_init_glfw;
		}
		glfwSetErrorCallback(
			[](int _error_code, const char* _description) -> void
			{
				LOG_ERROR("[Glfw Window ERROR] (code: {0}): {1}", _error_code, _description);
			});
		return std::nullopt;
	}



	std::optional<error::window_error> window::create(uint16_t _width, uint16_t _height) noexcept
	{
		auto result_ = __glfwInit();
		if (result_.has_value())
		{
			return result_;
		}

		m_window_data_.width = _width;
		m_window_data_.height = _height;

		m_window_ptr = glfwCreateWindow(m_window_data_.width, m_window_data_.height, m_window_data_.title.c_str(), nullptr, nullptr);
		if (!m_window_ptr)
		{
			LOG_CRITICAL("[Glfw Window ERROR] Can't create window '{0}'.", m_window_data_.title);
			return error::window_error::can_not_create;
		}
		glfwMakeContextCurrent(m_window_ptr);

		try
		{
			windows_manager::addNewWindow(shared_from_this());
		}
		catch (const std::exception& ex_)
		{
			LOG_CRITICAL("[Glfw Window ERROR] Can't add window '{0}' in windows manager: " + std::string(ex_.what()), m_window_data_.title);
			return error::window_error::can_not_add_new_window;
		}

		return std::nullopt;
	}



	void window::setWindowResizeCallBack() const noexcept
	{
		glfwSetWindowSizeCallback(m_window_ptr,
			[](GLFWwindow* _window_ptr, int _width, int _height) -> void
			{
				try
				{
					auto [window_data, call_backs] = windows_manager::getWindowDataAndCBS(_window_ptr);
					window_data.height = _height;
					window_data.width = _width;

					ResizeEventData resize_data = { window_data.height, window_data.width };
					call_backs.resize_call_back(resize_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled event: " + std::string(ex_.what()));
				}
			});
	}



	void window::setWindowCloseCallBack() const noexcept
	{
		glfwSetWindowCloseCallback(m_window_ptr,
			[](GLFWwindow* _window_ptr) -> void
			{
				try
				{
					auto [window_data, call_backs] = windows_manager::getWindowDataAndCBS(_window_ptr);
					call_backs.close_call_back();
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled event: " + std::string(ex_.what()));
				}
			});
	}



	void window::shutdown() noexcept
	{
		glfwDestroyWindow(m_window_ptr);
		windows_manager::closeWindow(m_window_ptr);
		if (windows_manager::getWindowsCount() == 0)
		{
			glfwTerminate();
		}
	}



	window::~window()
	{
		shutdown();
	}
}