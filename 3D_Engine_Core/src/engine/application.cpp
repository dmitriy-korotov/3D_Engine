#include <engine/application.hpp>

#include <engine/error.hpp>
#include <engine/logging/log.hpp>

#include <engine/window/glfw_window.hpp>
#include <engine/window/events_data.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



static bool m_is_created_ = false;



namespace engine
{
    Application::Application(std::uint16_t _width, std::uint16_t _height,
                             const std::string_view& _application_name)
            : m_window_ptr_(std::make_shared<glfw_window>(_application_name))
    { 
        if (m_window_ptr_->create(_width, _height).has_value())
        {
            LOG_CRITICAL("Can't create window '{0}' with size {1}x{2}.",
                         m_window_ptr_->getTitle(), m_window_ptr_->getWidth(), m_window_ptr_->getHeight());
            throw std::exception("Window not created.");
        };

        LOG_INFO("Application '{0}' started, size: {1}x{2}",
                 m_window_ptr_->getTitle(), m_window_ptr_->getWidth(), m_window_ptr_->getHeight());
    }



	Application Application::create(std::uint16_t _width, std::uint16_t _height,
                                    const std::string_view& _application_name)
	{
		if (m_is_created_)
		{
            LOG_ERROR("Application already exists.");
			throw std::logic_error("Application already exists.");
		}
        m_is_created_ = true;
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

        m_window_ptr_->addEventListener<window::Events::Resize>(
            [this](const window::ResizeEventData& _size) -> void
            {
                LOG_INFO("[RESIZE EVENT] Window '{0}', size: {1}x{2}", m_window_ptr_->getTitle(), _size.width, _size.height);
            });

        m_window_ptr_->addEventListener<window::Events::Close>(
            [this]() -> void
            {
                LOG_INFO("[CLOSE EVENT] Window '{0}' closed", m_window_ptr_->getTitle());
                m_is_closed_ = true;
            });

        while (!m_is_closed_)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            onUpdate();
            m_window_ptr_->onUpdate();
        }

        glfwTerminate();
        return std::nullopt;
	}



	void Application::onUpdate() const noexcept
	{ }



    Application::~Application()
    {
        LOG_INFO("Application '{0}' closed, size: {1}x{2}",
                  m_window_ptr_->getTitle(), m_window_ptr_->getWidth(), m_window_ptr_->getHeight());
    }
}