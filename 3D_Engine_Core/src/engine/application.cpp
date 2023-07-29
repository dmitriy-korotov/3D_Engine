#include <engine/application.hpp>

#include <engine/error.hpp>
#include <engine/logging/log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine
{
	bool Application::m_is_created = false;



	Application Application::create()
	{
		if (m_is_created)
		{
            LOG_ERROR("Application already exists.");
			throw std::logic_error("Application already exists.");
		}
        m_is_created = true;
		return Application();
	}



	std::optional<error::app_error> Application::start(std::uint16_t _width, std::uint16_t _height,
													   const std::string_view& _application_name) noexcept
	{
        GLFWwindow* window_ = nullptr;

        if (!glfwInit())
        {
            LOG_CRITICAL("Can't initializate glfw.");
            return error::app_error::can_not_create;
        }

        window_ = glfwCreateWindow(_width, _height, _application_name.data(), NULL, NULL);
        if (!window_)
        {
            LOG_CRITICAL("Can't create window.");
            glfwTerminate();
            return error::app_error::can_not_create;
        }

        glfwMakeContextCurrent(window_);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            LOG_CRITICAL("Can't load glad.");
            glfwTerminate();
            return error::app_error::can_not_create;
        }

        while (!glfwWindowShouldClose(window_))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window_);
            glfwPollEvents();

            onUpdate();
        }

        glfwTerminate();
        return std::nullopt;
	}



	void Application::onUpdate() const noexcept
	{ }
}