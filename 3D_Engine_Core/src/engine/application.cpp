#include <engine/application.hpp>

#include <engine/logging/log.hpp>

#include <engine/window/glfw/glfw_window.hpp>



namespace engine
{
    bool application::s_is_created = false;
    bool application::s_is_closed = false;





    application::application(std::uint16_t _width, std::uint16_t _height,
                             const std::string_view& _application_name)
            : m_window_ptr(std::make_shared<window::glfw::window>(_application_name))
    { 
        checkIsNotAlreadyCreated();
        if (m_window_ptr->create(_width, _height).has_value())
        {
            LOG_CRITICAL("[Application ERROR] Can't create window '{0}' with size {1}x{2}.",
                         m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
            throw std::exception("Can't create window.");
        }; 
    }



    void application::checkIsNotAlreadyCreated()
    {
        if (s_is_created)
        {
            LOG_ERROR("[Application ERROR] Application already exists.");
            throw std::logic_error("Application already exists.");
        }
        s_is_created = true;
    }



	void application::start() noexcept
	{
        while (!s_is_closed)
        {
            m_window_ptr->onUpdate();
            onUpdate();
        }
	}



    void application::close() noexcept
    {
        s_is_closed = true;
    }



	void application::onUpdate() noexcept
	{ }
}