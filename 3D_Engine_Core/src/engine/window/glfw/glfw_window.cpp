#include <engine/window/glfw/glfw_window.hpp>

#include <engine/input/keyboard.hpp>
#include <engine/input/mouse.hpp>

#include <engine/error/window_error.hpp>
#include <engine/logging/log.hpp>

#include <engine/window/windows_manager.hpp>

#include <engine/render/image.hpp>

#include <engine/window/glfw/glfw.hpp>

#include <GLFW/glfw3.h>



namespace engine::window::glfw
{
	static window_id_t generateWindowID(glfw_window::glfw_window_ptr_t _window) noexcept
	{
		return std::hash<glfw_window::glfw_window_ptr_t>::_Do_hash(_window);
	}





	glm::dvec2 glfw_window::getCurrentCursorPosition() const noexcept
	{
		double x = 0;
		double y = 0;
		glfw::instance().getCurrentCursorPosition(m_window_ptr, x, y);
		return { x, y };
	}



	void glfw_window::setupIcon(const path& _path_to_icon) const noexcept
	{
		render::image icon(_path_to_icon);
		if (icon.isLoaded())
		{
			glfw::instance().setWindowIcon(m_window_ptr, icon);
		}
		else
		{
			LOG_ERROR("[Window Glfw ERROR] Can't load icon: {0}.", _path_to_icon.generic_string());
		}
	}



	void glfw_window::onUpdate() noexcept
	{
		glfw::instance().pollEvents();
		glfw::instance().makeContextCurrent(m_window_ptr);
		glfw::instance().swapBuffers(m_window_ptr);
	}



	glfw_window::window_err glfw_window::createWindow(OpenMode _open_mode) noexcept
	{
		if (_open_mode == OpenMode::FullScreen)
		{
			monitor monitor = glfw::instance().getPrimaryMonitor();
			video_mode mode = glfw::instance().getVideoMode(monitor);

			m_window_ptr = glfw::instance().createWindow(m_width, m_height, m_title, monitor);
		}
		else
		{
			m_window_ptr = glfw::instance().createWindow(m_width, m_height, m_title, nullptr);
		}

		if (!m_window_ptr)
		{
			LOG_CRITICAL("[Glfw Window ERROR] Can't create window '{0}'.", m_title);
			return error::window_error::can_not_create;
		}
		glfw::instance().makeContextCurrent(m_window_ptr);
		return std::nullopt;
	}



	glfw_window::window_err glfw_window::create(const std::string_view& _title, uint16_t _width,
												uint16_t _height, OpenMode _open_mode) noexcept
	{
		if (!glfw::instance().isInited())
		{
			return error::window_error::can_not_init_glfw;
		}

		m_title = _title;
		m_width = _width;
		m_height = _height;

		auto is_glfw_window_created_ = createWindow(_open_mode);
		if (is_glfw_window_created_.has_value())
		{
			return is_glfw_window_created_;
		}
		m_id = generateWindowID(m_window_ptr);

		try
		{
			windows_manager::instance().addNewWindow(getID(), shared_from_this());
		}
		catch (const std::exception& ex_)
		{
			LOG_CRITICAL("[Glfw Window ERROR] Can't add window '{1}' in windows manager: {0}.", std::string(ex_.what()), m_title);
			return error::window_error::can_not_add_new_window;
		}

		return std::nullopt;
	}



	void glfw_window::setWindowResizeCallBack() const noexcept
	{
		glfw::instance().setWindowResizeCallBack(m_window_ptr,
			[](glfw_window_ptr_t _window_ptr, int _width, int _height) -> void
			{
				try
				{
					auto window = windows_manager::instance().getWindow(generateWindowID(_window_ptr));
					
					window->setWidth(_width);
					window->setHeight(_height);

					ResizeEventData resize_data = { window->getWidth(), window->getHeight() };
					window->getCallBacksStorage().resize_call_back(resize_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'resize' event: {0}.", std::string(ex_.what()));
				}
			});
	}



	void glfw_window::setWindowCloseCallBack() const noexcept
	{
		glfw::instance().setWindowCloseCallBack(m_window_ptr,
			[](glfw_window_ptr_t _window_ptr) -> void
			{
				try
				{
					auto window = windows_manager::instance().getWindow(generateWindowID(_window_ptr));
					window->getCallBacksStorage().close_call_back();
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'window close' event: {0}.", std::string(ex_.what()));
				}
			});
	}



	void glfw_window::setKeyboardInputCallBack() const noexcept
	{
		glfw::instance().setKeyCallback(m_window_ptr,
			[](glfw_window_ptr_t _window_ptr, int _key_code, int _scancode, int _action, int _mode) -> void
			{
				try
				{
					auto window = windows_manager::instance().getWindow(generateWindowID(_window_ptr));

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
					window->getCallBacksStorage().keyboard_input_call_back(keyboard_input_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'keyboard input' event: {0}.", std::string(ex_.what()));
				}
			}
		);
	}



	void glfw_window::setMouseInputCallBack() const noexcept
	{
		glfw::instance().setMouseButtonCallback(m_window_ptr,
			[](glfw_window_ptr_t _window_ptr, int _button, int _action, int _mods) -> void
			{
				try
				{
					auto window = windows_manager::instance().getWindow(generateWindowID(_window_ptr));

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
					window->getCallBacksStorage().mouse_input_call_back(mouse_input_data);
				}
				catch (const std::exception& ex_)
				{
					LOG_ERROR("[Glfw Window ERROR] Window catched exception when handeled 'mouse input' event: {0}.", std::string(ex_.what()));
				}
			});
	}



	void glfw_window::shutdown() noexcept
	{
		glfw::instance().destroyWindow(m_window_ptr);
	}



	glfw_window::~glfw_window()
	{
		shutdown();
	}
}