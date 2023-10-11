#include <engine/application.hpp>

#include <engine/logging/log.hpp>

#include <engine/names_settings.hpp>
#include <engine/application_settings.hpp>

#include <engine/window/basic_window.hpp>
#include <engine/window/events_data.hpp>
#include <engine/window/glfw/glfw_window_context.hpp>

#include <engine/render/application_renderer.hpp>
#include <engine/render/open_gl/renderer_open_gl.hpp>

#include <engine/input/mouse.hpp>
#include <engine/input/keyboard.hpp>

#include <nlohmann/json.hpp>

#include <fstream>



using namespace engine::window;
using namespace engine::render;

namespace engine
{
    using nlohmann::json;





    application& application::instance() noexcept
    {
        static application instance;
        return instance;
    }



    void application::setConfig(const path& _path_to_config_file) noexcept
    {
        if (std::filesystem::exists(_path_to_config_file))
            m_path_to_config = _path_to_config_file;
        else
            LOG_ERROR("[Application ERROR] Config file is not exists (file: {0}).", _path_to_config_file.generic_string());
    }



    const std::optional<path>& application::getPathToConfig() const noexcept
    {
        return m_path_to_config;
    }



    application::app_error application::loadConfig() noexcept
    {
        RendererImpl renderer_impl =                application_settings::instance().getRendererImpl();
        UIModuleImpl UI_module_impl =               application_settings::instance().getUIModuleImpl();
        WindowImpl window_impl =                    application_settings::instance().getWindowImpl();
        std::string title =                         application_settings::instance().getTitle();
        uint16_t width =                            application_settings::instance().getWidth();
        uint16_t height =                           application_settings::instance().getHeight();
        OpenMode open_mode =                        application_settings::instance().getOpenMode();
        std::optional<path> path_to_window_icon =   application_settings::instance().getPathToWindowIcon();



        if (m_path_to_config.has_value())
        {
            std::ifstream file_with_settings(m_path_to_config.value());
            if (file_with_settings.is_open())
            {
                json settings = json::parse(file_with_settings);



                // setup window settings
                if (settings.find(WINDOW_IMPL_SETTING_NAME) != settings.end())
                {
                    window_impl = toWindowImpl(settings[WINDOW_IMPL_SETTING_NAME]);
                    application_settings::instance().setWindowImpl(window_impl);
                }
                if (settings.find(TITLE_SETTING_NAME) != settings.end())
                {
                    title = settings[TITLE_SETTING_NAME];
                    application_settings::instance().setTitle(title);
                }
                if (settings.find(WIDTH_SETTING_NAME) != settings.end())
                {
                    width = settings[WIDTH_SETTING_NAME];
                    application_settings::instance().setWidth(width);
                }
                if (settings.find(HEIGHT_SETTING_NAME) != settings.end())
                {
                    height = settings[HEIGHT_SETTING_NAME];
                    application_settings::instance().setHeight(height);
                }
                if (settings.find(OPEN_MODE_SETTING_NAME) != settings.end())
                {
                    open_mode = toOpenMode(settings[OPEN_MODE_SETTING_NAME]);
                    application_settings::instance().setOpenMode(open_mode);
                }
                if (settings.find(PATH_TO_WINDOW_ICON_NAME) != settings.end())
                {
                    path_to_window_icon = std::string(settings[PATH_TO_WINDOW_ICON_NAME]);
                    application_settings::instance().setPathToWindowIcon(path_to_window_icon.value());
                }



                // setup renderer settings
                if (settings.find(RENDERER_IMPL_SETTING_NAME) != settings.end())
                {
                    renderer_impl = toRendererImpl(settings[RENDERER_IMPL_SETTING_NAME]);
                    application_settings::instance().setRendererImpl(renderer_impl);
                }



                // setup UIModule settings
                if (settings.find(UI_MODULE_IMPL_SETTING_NAME) != settings.end())
                {
                    UI_module_impl = toUIModuleImpl(settings[UI_MODULE_IMPL_SETTING_NAME]);
                    application_settings::instance().setUIModuleImpl(UI_module_impl);
                }
            }
            else
            {
                LOG_ERROR("[Application ERROR] Can't open config file: {0}", m_path_to_config->generic_string());
                return error::application_error::can_not_load_config;
            }
        }
        return std::nullopt;
    }



    application::app_error application::createWindow() noexcept
    {
        WindowImpl window_impl =                    application_settings::instance().getWindowImpl();
        std::string title =                         application_settings::instance().getTitle();
        uint16_t width =                            application_settings::instance().getWidth();
        uint16_t height =                           application_settings::instance().getHeight();
        OpenMode open_mode =                        application_settings::instance().getOpenMode();
        std::optional<path> path_to_window_icon =   application_settings::instance().getPathToWindowIcon();



        switch (window_impl)
        {
        case WindowImpl::GLFW:
            m_window_context = std::make_shared<glfw::glfw_window_context>();
            m_window_context->init();
            m_window_ptr = m_window_context->createWindow();
            break;
        case WindowImpl::SDL:
            break;
        case WindowImpl::SFML:
            break;
        }



        if (m_window_ptr->create(title, width, height, open_mode).has_value())
            return error::application_error::can_not_create_window;

        if (path_to_window_icon.has_value())
            m_window_ptr->setupIcon(path_to_window_icon.value());

        return std::nullopt;
    }



    application::app_error application::setupRenderer() noexcept
    {
        std::shared_ptr<basic_renderer> renderer;

        switch (application_settings::instance().getRendererImpl())
        {
        case RendererImpl::OpenGL:
            renderer = std::shared_ptr<open_gl::renderer>(&open_gl::renderer::instance(),
                                                          [](open_gl::renderer* _renderer) -> void
                                                          { });
            break;
        case RendererImpl::Direct3D:
            break;
        case RendererImpl::DirectX:
            break;
        case RendererImpl::Vulkan:
            break;
        }

        if (!renderer->init(application_settings::instance().getWindowImpl()))
            return error::application_error::can_not_setup_renderer;

        //renderer->enableDepthTest();

        application_renderer::instance().setupRenderer(std::move(renderer));

        return std::nullopt;
    }



    void application::setWindowEventHandlers() noexcept
    {
        m_window_ptr->addEventListener<Events::Resize>(
            [this](const ResizeEventData& _size) -> void
            {
                application_settings::instance().setWidth(_size.width);
                application_settings::instance().setHeight(_size.height);

                onWindowResize();
            });

        m_window_ptr->addEventListener<Events::Close>(
            [this]() -> void
            {
                close();
                onWindowClose();
            });

        m_window_ptr->addEventListener<Events::KeyboardInput>(
            [this](const KeyboardInputEventData& _keyboard_input_data) -> void
            {
                if (_keyboard_input_data.action == input::Action::Released)
                    input::keyboard::releaseKey(_keyboard_input_data.key);
                else if (_keyboard_input_data.action == input::Action::Pressed)
                    input::keyboard::pressKey(_keyboard_input_data.key);

                onKeyboardInput();
            });

        m_window_ptr->addEventListener<Events::MouseInput>(
            [this](const MouseInputEventData& _mouse_input_data) -> void
            {
                if (_mouse_input_data.action == input::Action::Released)
                    input::mouse::releaseButton(_mouse_input_data.key);
                else if (_mouse_input_data.action == input::Action::Pressed)
                    input::mouse::pressButton(_mouse_input_data.key);

                onMouseInput();
            });

        m_window_ptr->addEventListener<Events::MouseMove>(
            [this](const MouseMoveEventData _mouse_move_data) -> void
            {
                input::mouse::setCursorPosition(_mouse_move_data.x, _mouse_move_data.y);
            });
    }



	application::app_error application::start() noexcept
	{
        auto cfg_error = loadConfig();
        if (cfg_error.has_value())
            return cfg_error;

        auto wind_error = createWindow();
        if (wind_error.has_value())
            return wind_error;

        auto render_error = setupRenderer();
        if (render_error.has_value())
            return render_error;

        setWindowEventHandlers();

        onStart();

        m_is_closed = false;
        while (!isClosed())
        {
            m_window_ptr->onUpdate();
            onUpdate();
            onDrawUI();
        }

        onClose();
        m_window_ptr->shutdown();
        m_window_context->terminate();

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
    void application::onStart() noexcept
    { }
    void application::onClose() noexcept
    { }



    void application::onWindowResize() noexcept
    { }
    void application::onWindowClose() noexcept
    { }
    void application::onWindowMove() noexcept
    { }
    void application::onMouseMove() noexcept
    { }
    void application::onMouseInput() noexcept
    { }
    void application::onKeyboardInput() noexcept
    { }
}