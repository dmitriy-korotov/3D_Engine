#include <engine/application.hpp>

#include <engine/error.hpp>
#include <engine/logging/log.hpp>

#include <engine/window/window_gui.hpp>
#include <engine/window/events_data.hpp>
#include <engine/window/windows_manager.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



static bool s_is_created = false;



namespace engine
{
    Application::Application(std::uint16_t _width, std::uint16_t _height,
                             const std::string_view& _application_name)
            : m_window_ptr(std::make_shared<window_gui>(_application_name))
    { 
        if (m_window_ptr->create(_width, _height).has_value())
        {
            LOG_CRITICAL("Can't create window '{0}' with size {1}x{2}.",
                         m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
            throw std::exception("Window not created.");
        };

        LOG_INFO("Application '{0}' started, size: {1}x{2}",
                 m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
    }



	Application Application::create(std::uint16_t _width, std::uint16_t _height,
                                    const std::string_view& _application_name)
	{
		if (s_is_created)
		{
            LOG_ERROR("Application already exists.");
			throw std::logic_error("Application already exists.");
		}
        s_is_created = true;
		return Application(_width, _height, _application_name);
	}



	std::optional<error::app_error> Application::start() noexcept
	{
        m_window_ptr->addEventListener<window::Events::Resize>(
            [this](const window::ResizeEventData& _size) -> void
            {
                LOG_INFO("[RESIZE EVENT] Window '{0}', size: {1}x{2}", m_window_ptr->getTitle(), _size.width, _size.height);
                glViewport(0, 0, _size.width, _size.height);
            });

        m_window_ptr->addEventListener<window::Events::Close>(
            [this]() -> void
            {
                LOG_INFO("[CLOSE EVENT] Window '{0}' closed", m_window_ptr->getTitle());
                m_is_closed = true;
            });

        while (!m_is_closed)
        {
            onUpdate();
            m_window_ptr->onUpdate();
        }

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