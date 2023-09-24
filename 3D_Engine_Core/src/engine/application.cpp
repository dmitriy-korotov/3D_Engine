#include <engine/application.hpp>

#include <engine/application_settings.hpp>

#include <engine/logging/log.hpp>

#include <engine/window/glfw/glfw_window.hpp>



namespace engine
{
    application& application::instance() noexcept
    {
        static application instance;
        return instance;
    }



    void application::setConfig(const path& _path_to_config_file) noexcept
    {
        if (std::filesystem::exists(_path_to_config_file))
        {
            m_path_to_config = _path_to_config_file;
        }
        else
        {
            LOG_ERROR("[Application ERROR] Config file is not exists (file: {0}).", _path_to_config_file.generic_string());
        }
    }



    void application::loadConfig() noexcept
    {
        if (m_path_to_config.has_value())
        {

        }
        else
        {
            m_window_ptr = std::make_shared<window::glfw::glfw_window>();
            m_window_ptr->create(application_settings::instance().getTitle(),
                                 application_settings::instance().getWidth(),
                                 application_settings::instance().getHeight(),
                                 application_settings::instance().getOpenMode());
        }
    }



	void application::start() noexcept
	{
        loadConfig();
        m_is_closed = false;
        while (!isClosed())
        {
            m_window_ptr->onUpdate();
            onUpdate();
        }
	}



    bool application::isClosed() const noexcept
    {
        return m_is_closed;
    }



    void application::close() noexcept
    {
        m_is_closed = true;
    }



	void application::onUpdate() noexcept
	{ }
}