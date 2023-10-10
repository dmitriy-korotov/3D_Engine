#include <engine/names_settings.hpp>



using namespace engine::window;
using namespace engine::render;

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



    render::RendererImpl toRendererImpl(const std::string_view& _str_renderer_impl) noexcept
    {
        if (_str_renderer_impl == OPEN_GL_IMPL)             return RendererImpl::OpenGL;
        if (_str_renderer_impl == DIRECT_X_IMPL)            return RendererImpl::DirectX;
        if (_str_renderer_impl == DIRECT_3D_IMPL)           return RendererImpl::Direct3D;
        if (_str_renderer_impl == VULCAN_IMPL)              return RendererImpl::Vulkan;

        return RendererImpl::OpenGL;
    }
}