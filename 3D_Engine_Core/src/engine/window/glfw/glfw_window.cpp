#include <engine/window/glfw/glfw_window.hpp>

#include <engine/input/keyboard.hpp>
#include <engine/input/mouse.hpp>

#include <engine/error/window_error.hpp>
#include <engine/logging/log.hpp>

#include <engine/window/glfw/windows_manager.hpp>

#include <engine/image.hpp>

#include <GLFW/glfw3.h>



namespace engine::window::glfw
{
	window::window(const std::string_view& _title)
			: basic_window(_title)
	{ }



	glm::dvec2 window::getCurrentCursorPosition() const noexcept
	{
		double x = 0;
		double y = 0;
		glfwGetCursorPos(m_window_ptr, &x, &y);
		
		return { x, y };
	}



	void window::setupIcon(const std::filesystem::path& _path_to_icon) const noexcept
	{
		image icon(_path_to_icon);
		if (icon.isLoaded())
		{
			GLFWimage glfw_icon;
			glfw_icon.pixels = icon.getData();
			glfw_icon.height = icon.getHeight();
			glfw_icon.width = icon.getWidth();
			glfwSetWindowIcon(m_window_ptr, 1, &glfw_icon);
		}
		else
		{
			LOG_ERROR("[Window Glfw ERROR] Can't load icon: {0}.", _path_to_icon.generic_string());
		}
	}



	void window::onUpdate() noexcept
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window_ptr);
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



	std::optional<error::window_error> window::__createGlfwWindow(bool _is_full_screen_mode) noexcept
	{
		if (_is_full_screen_mode)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			m_window_ptr = glfwCreateWindow(mode->width, mode->height, m_window_data_.title.c_str(), monitor, nullptr);
		}
		else
		{
			m_window_ptr = glfwCreateWindow(m_window_data_.width, m_window_data_.height, m_window_data_.title.c_str(), nullptr, nullptr);
		}

		if (!m_window_ptr)
		{
			LOG_CRITICAL("[Glfw Window ERROR] Can't create window '{0}'.", m_window_data_.title);
			return error::window_error::can_not_create;
		}
		glfwMakeContextCurrent(m_window_ptr);
		return std::nullopt;
	}



	std::optional<error::window_error> window::create(uint16_t _width, uint16_t _height, bool _is_full_screen_mode) noexcept
	{
		auto is_glfw_inited_ = __glfwInit();
		if (is_glfw_inited_.has_value())
		{
			return is_glfw_inited_;
		}

		m_window_data_.width = _width;
		m_window_data_.height = _height;

		auto is_glfw_window_created_ = __createGlfwWindow(_is_full_screen_mode);
		if (is_glfw_window_created_.has_value())
		{
			return is_glfw_window_created_;
		}

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

					ResizeEventData resize_data = { window_data.width, window_data.height };
					call_backs.resize_call_back(resize_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'resize' event: " + std::string(ex_.what()));
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
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'window close' event: " + std::string(ex_.what()));
				}
			});
	}



	void window::setKeyboardInputCallBack() const noexcept
	{
		glfwSetKeyCallback(m_window_ptr,
			[](GLFWwindow* _window_ptr, int _key_code, int _scancode, int _action, int _mode) -> void
			{
				try
				{
					auto [window_data, call_backs] = windows_manager::getWindowDataAndCBS(_window_ptr);

					KeyboardInputEventData keyboard_input_data = { static_cast<input::Key>(_key_code),
																   static_cast<input::Action>(_action) };

					if (keyboard_input_data.action == input::Action::Released)
					{
						input::keyboard::releaseKey(static_cast<input::Key>(_key_code));
						
					}
					else if (keyboard_input_data.action == input::Action::Pressed)
					{
						input::keyboard::pressKey(static_cast<input::Key>(_key_code));
						
					}
					call_backs.keyboard_input_call_back(keyboard_input_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'keyboard input' event: " + std::string(ex_.what()));
				}
			}
		);
	}



	void window::setMouseInputCallBack() const noexcept
	{
		glfwSetMouseButtonCallback(m_window_ptr,
			[](GLFWwindow* _window_ptr, int _button, int _action, int _mods) -> void
			{
				try
				{
					auto [window_data, call_backs] = windows_manager::getWindowDataAndCBS(_window_ptr);

					MouseInputEventData mouse_input_data = { static_cast<input::MouseButton>(_button),
															 static_cast<input::Action>(_action) };

					if (mouse_input_data.action == input::Action::Released)
					{
						input::mouse::releaseButton(static_cast<input::MouseButton>(_button));

					}
					else if (mouse_input_data.action == input::Action::Pressed)
					{
						input::mouse::pressButton(static_cast<input::MouseButton>(_button));

					}
					call_backs.mouse_input_call_back(mouse_input_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'mouse input' event: " + std::string(ex_.what()));
				}
			});
	}



	void window::shutdown() noexcept
	{
		glfwDestroyWindow(m_window_ptr);
		glfwTerminate();
	}



	window::~window()
	{
		shutdown();
	}
}