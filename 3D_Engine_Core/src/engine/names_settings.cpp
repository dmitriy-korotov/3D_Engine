#include <engine/names_settings.hpp>



using namespace engine::window;

namespace engine
{
    WindowImpl toWindowImpl(const std::string_view& _str_window_impl) noexcept
    {
        if (_str_window_impl == GLFW_IMPLE)           return WindowImpl::GLFW;
        if (_str_window_impl == SDL_IMPL)             return WindowImpl::SDL;
        if (_str_window_impl == SFML_IMPL)            return WindowImpl::SFML;

        return WindowImpl::GLFW;
    }



    OpenMode toOpenMode(const std::string_view& _str_open_mode) noexcept
    {
        if (_str_open_mode == FULL_SCREEN_OPEN_MODE)        return OpenMode::FullScreen;
        if (_str_open_mode == IN_WINDOW_OPEN_MODE)          return OpenMode::InWindow;

        return OpenMode::FullScreen;
    }
}