#include <engine/application.hpp>

#include <engine/error.hpp>
#include <engine/logging/log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine
{
	bool Application::m_is_created = false;





    Application::Application(std::uint16_t _width, std::uint16_t _height,
                             const std::string_view& _application_name)
            : m_window_ptr(std::make_unique<Window>(_width, _height, _application_name))
    { 
        LOG_INFO("Application '{0}' started, size: {1}x{2}",
                 m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
    }



	Application Application::create(std::uint16_t _width, std::uint16_t _height,
                                    const std::string_view& _application_name)
	{
		if (m_is_created)
		{
            LOG_ERROR("Application already exists.");
			throw std::logic_error("Application already exists.");
		}
        m_is_created = true;
		return Application(_width, _height, _application_name);
	}



	std::optional<error::app_error> Application::start() noexcept
	{

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            LOG_CRITICAL("Can't load glad.");
            glfwTerminate();
            return error::app_error::can_not_create;
        }

        while (!m_window_ptr->isShouldClose())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            onUpdate();
            m_window_ptr->onUpdate();
        }

        glfwTerminate();
        return std::nullopt;
	}



	void Application::onUpdate() const noexcept
	{ }



    Application::~Application()
    {
        LOG_INFO("Application '{0}' closed, size: {1}x{2}",
                  m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
    }
}