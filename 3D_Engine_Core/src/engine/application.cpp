#include <engine/application.hpp>

#include <engine/error.hpp>

#include <GLFW/glfw3.h>



namespace engine
{
	bool Application::is_created = false;



	Application Application::create()
	{
		if (is_created)
		{
			throw std::logic_error("Application already exists.");
		}
		return Application();
	}



	std::optional<error::app_error> Application::start(std::uint16_t _width, std::uint16_t _height,
													   const std::string_view& _application_name) noexcept
	{
        GLFWwindow* window_ = nullptr;

        if (!glfwInit())
            return error::app_error::can_not_create;

        window_ = glfwCreateWindow(_width, _height, _application_name.data(), NULL, NULL);
        if (!window_)
        {
            glfwTerminate();
            return error::app_error::can_not_create;
        }

        glfwMakeContextCurrent(window_);

        while (!glfwWindowShouldClose(window_))
        {
            //glClear(GL_COLOR_BUFFER_BIT);
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