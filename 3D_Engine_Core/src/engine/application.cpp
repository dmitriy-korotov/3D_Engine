#include <engine/application.hpp>

#include <engine/names_settings.hpp>
#include <engine/application_settings.hpp>

#include <engine/logging/log.hpp>

#include <engine/window/glfw/glfw_window.hpp>

#include <nlohmann/json.hpp>

#include <fstream>



namespace engine
{
    using nlohmann::json;



    static constexpr WindowImpl toWindowImpl(const std::string_view& _str_window_impl) noexcept
    {
        if (_str_window_impl == GLFW_IMPLE)           return WindowImpl::GLFW;
        if (_str_window_impl == SDL_IMPL)             return WindowImpl::SDL;
        if (_str_window_impl == SFML_IMPL)            return WindowImpl::SFML;

        return WindowImpl::GLFW;
    }



    static constexpr OpenMode toOpenMode(const std::string_view& _str_open_mode) noexcept
    {
        if (_str_open_mode == FULL_SCREEN_OPEN_MODE)        return OpenMode::FullScreen;
        if (_str_open_mode == IN_WINDOW_OPEN_MODE)          return OpenMode::InWindow;

        return OpenMode::FullScreen;
    }





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



    application::app_error application::loadConfig() noexcept
    {
        WindowImpl window_impl = application_settings::instance().getWindowImpl();
        std::string title = application_settings::instance().getTitle();
        uint16_t width = application_settings::instance().getWidth();
        uint16_t height = application_settings::instance().getHeight();
        OpenMode open_mode = application_settings::instance().getOpenMode();
        std::optional<path> path_to_window_icon = application_settings::instance().getPathToWindowIcon();

        if (m_path_to_config.has_value())
        {
            std::ifstream file_with_settings(m_path_to_config.value());
            if (file_with_settings.is_open())
            {
                json settings = json::parse(file_with_settings);
                if (settings.find(WINDOW_IMPL_SETTING_NAME) != settings.end())
                {
                    window_impl = toWindowImpl(settings[WINDOW_IMPL_SETTING_NAME]);
                }
                if (settings.find(TITLE_SETTING_NAME) != settings.end())
                {
                    title = settings[TITLE_SETTING_NAME];
                }
                if (settings.find(WIDTH_SETTING_NAME) != settings.end())
                {
                    width = settings[WIDTH_SETTING_NAME];
                }
                if (settings.find(HEIGHT_SETTING_NAME) != settings.end())
                {
                    height = settings[HEIGHT_SETTING_NAME];
                }
                if (settings.find(OPEN_MODE_SETTING_NAME) != settings.end())
                {
                    open_mode = toOpenMode(settings[OPEN_MODE_SETTING_NAME]);
                }
                if (settings.find(PATH_TO_WINDOW_ICON_NAME) != settings.end())
                {
                    path_to_window_icon = std::string(settings[PATH_TO_WINDOW_ICON_NAME]);
                }
            }
            else
            {
                LOG_ERROR("[Application ERROR] Can't open config file: {0}", m_path_to_config->generic_string());
            }
        }

        switch (window_impl)
        {
        case engine::window::WindowImpl::GLFW:
            m_window_ptr = std::make_shared<window::glfw::glfw_window>();
            break;
        case engine::window::WindowImpl::SDL:
            break;
        case engine::window::WindowImpl::SFML:
            break;
        }

        if (m_window_ptr->create(title, width, height, open_mode).has_value())
        {
            return error::application_error::can_not_create_window;
        }
        if (path_to_window_icon.has_value())
        {
            m_window_ptr->setupIcon(path_to_window_icon.value());
        }
        return std::nullopt;
    }



    void application::onStart() noexcept
    { }



	application::app_error application::start() noexcept
	{
        auto error = loadConfig();
        if (error.has_value())
        {
            return error;
        }

        onStart();

        m_is_closed = false;
        while (!isClosed())
        {
            m_window_ptr->onUpdate();
            onUpdate();
            onDrawUI();
        }

        onClose();

        return std::nullopt;
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
    void application::onDrawUI() noexcept
    { }
    void application::onClose() noexcept
    { }
}