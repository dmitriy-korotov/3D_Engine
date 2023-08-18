#include <engine/window/glfw_window.hpp>

#include <engine/error.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



static bool s_glfw_ininted_ = false;



namespace engine
{
	glfw_window::glfw_window(const std::string_view& _title)
			: basic_window(_title)
	{ }



	void glfw_window::onUpdate() noexcept
	{
		glfwSwapBuffers(m_window_ptr_);
		glfwPollEvents();
	}



	std::optional<error::window_error> glfw_window::__glfwInit() const noexcept
	{
		if (!s_glfw_ininted_)
		{
			if (!glfwInit())
			{
				LOG_CRITICAL("Can't initializate glfw.");
				return error::window_error::can_not_create;
			}
			s_glfw_ininted_ = true;
		}
		return std::nullopt;
	}



	std::optional<error::window_error> glfw_window::create(std::uint16_t _width, std::uint16_t _height) noexcept
	{
		auto result_ = __glfwInit();
		if (result_.has_value())
		{
			return result_;
		}

		m_window_data_.width = _width;
		m_window_data_.height = _height;

		m_window_ptr_ = glfwCreateWindow(m_window_data_.width, m_window_data_.height, m_window_data_.title.c_str(), nullptr, nullptr);
		if (!m_window_ptr_)
		{
			LOG_CRITICAL("Can't create window '{0}'.", m_window_data_.title);
			glfwTerminate();
			return error::window_error::can_not_create;
		}
		glfwMakeContextCurrent(m_window_ptr_);

		try
		{
			windows_manager::addNewWindow(shared_from_this());
		}
		catch (const std::exception& ex_)
		{
			LOG_CRITICAL("Can't add window '{0}' in windows manager: " + std::string(ex_.what()), m_window_data_.title);
			glfwTerminate();
			return error::window_error::can_not_add_new_window;
		}

		return std::nullopt;
	}



	void glfw_window::shutdown() noexcept
	{
		glfwDestroyWindow(m_window_ptr_);
		glfwTerminate();
	}



	glfw_window::~glfw_window()
	{
		shutdown();
	}
}