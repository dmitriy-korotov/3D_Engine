#include <engine/application.hpp>

#include <engine/logging/log.hpp>

#include <engine/names_settings.hpp>
#include <engine/application_settings.hpp>

#include <engine/window/basic_window.hpp>
#include <engine/window/events.hpp>
#include <engine/window/glfw/glfw_window_context.hpp>

#include <engine/input/mouse.hpp>
#include <engine/input/keyboard.hpp>

#include <engine/Engine.hpp>
#include <engine/render/open_gl/renderer.hpp>
#include <engine/modules/ui/imgui/UIModule.hpp>

#include <engine/resource_manager.hpp>
#include <engine/render/open_gl/shader_programs_creator.hpp>

#include <nlohmann/json.hpp>

#include <fstream>





using namespace engine::window;
using namespace engine::render;
using namespace engine::modules::ui;
using namespace nlohmann;

namespace engine
{
    auto application::instance() noexcept -> application&
    {
        static application instance;
        return instance;
    }



    auto application::setConfig(const path& _path_to_config_file) noexcept -> void
    {
        if (std::filesystem::exists(_path_to_config_file))
            m_path_to_config = _path_to_config_file;
        else
            LOG_ERROR("[Application ERROR] Config file is not exists (file: {0}).", _path_to_config_file.generic_string());
    }



    auto application::getPathToConfig() const noexcept -> const std::optional<path>&
    {
        return m_path_to_config;
    }



    auto application::loadConfig() noexcept -> app_error_t
    {
        RendererImpl renderer_impl =                getSettings().getRendererImpl();
        UIModuleImpl UI_module_impl =               getSettings().getUIModuleImpl();
        WindowImpl window_impl =                    getSettings().getWindowImpl();
        std::string title =                         getSettings().getTitle();
        uint16_t width =                            getSettings().getWidth();
        uint16_t height =                           getSettings().getHeight();
        OpenMode open_mode =                        getSettings().getOpenMode();
        std::optional<path> path_to_window_icon =   getSettings().getPathToWindowIcon();



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
                    getSettings().setWindowImpl(window_impl);
                }
                if (settings.find(TITLE_SETTING_NAME) != settings.end())
                {
                    title = settings[TITLE_SETTING_NAME];
                    getSettings().setTitle(title);
                }
                if (settings.find(WIDTH_SETTING_NAME) != settings.end())
                {
                    width = settings[WIDTH_SETTING_NAME];
                    getSettings().setWidth(width);
                }
                if (settings.find(HEIGHT_SETTING_NAME) != settings.end())
                {
                    height = settings[HEIGHT_SETTING_NAME];
                    getSettings().setHeight(height);
                }
                if (settings.find(OPEN_MODE_SETTING_NAME) != settings.end())
                {
                    open_mode = toOpenMode(settings[OPEN_MODE_SETTING_NAME]);
                    getSettings().setOpenMode(open_mode);
                }
                if (settings.find(PATH_TO_WINDOW_ICON_NAME) != settings.end())
                {
                    path_to_window_icon = std::string(settings[PATH_TO_WINDOW_ICON_NAME]);
                    getSettings().setPathToWindowIcon(path_to_window_icon.value());
                }



                // setup renderer settings
                if (settings.find(RENDERER_IMPL_SETTING_NAME) != settings.end())
                {
                    renderer_impl = toRendererImpl(settings[RENDERER_IMPL_SETTING_NAME]);
                    getSettings().setRendererImpl(renderer_impl);
                }



                // setup UIModule settings
                if (settings.find(UI_MODULE_IMPL_SETTING_NAME) != settings.end())
                {
                    UI_module_impl = toUIModuleImpl(settings[UI_MODULE_IMPL_SETTING_NAME]);
                    getSettings().setUIModuleImpl(UI_module_impl);
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



    auto application::createWindow() noexcept -> app_error_t
    {
        WindowImpl window_impl =                    getSettings().getWindowImpl();
        std::string title =                         getSettings().getTitle();
        uint16_t width =                            getSettings().getWidth();
        uint16_t height =                           getSettings().getHeight();
        OpenMode open_mode =                        getSettings().getOpenMode();
        std::optional<path> path_to_window_icon =   getSettings().getPathToWindowIcon();



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

        getSettings().setWidth(m_window_ptr->getWidth());
        getSettings().setHeight(m_window_ptr->getHeight());

        if (path_to_window_icon.has_value())
            m_window_ptr->setupIcon(path_to_window_icon.value());

        return std::nullopt;
    }



    auto application::setupRenderer() noexcept -> app_error_t
    {
        std::shared_ptr<basic_renderer> renderer = nullptr;

        switch (getSettings().getRendererImpl())
        {
        case RendererImpl::OpenGL:
            renderer = std::shared_ptr<open_gl::renderer>(&open_gl::renderer::instance(),
                                                          [](open_gl::renderer*) -> void
                                                          { });

            engine::GetResourceManager().getShadersManager().setupShaderProgramsCreator(std::make_unique<open_gl::shader_programs_creator>());

            break;
        case RendererImpl::Direct3D:
            break;
        case RendererImpl::DirectX:
            break;
        case RendererImpl::Vulkan:
            break;
        }

        if (!renderer->init(getSettings().getWindowImpl()))
            return error::application_error::can_not_setup_renderer;

        renderer->enableDepthTest();

        Engine::setApplicationRenderer(std::move(renderer));

        return std::nullopt;
    }



    auto application::setupUIModule() noexcept -> app_error_t
    {
        UIModuleImpl UI_module_impl = getSettings().getUIModuleImpl();
        RendererImpl renderer_impl =  getSettings().getRendererImpl();
        WindowImpl window_impl =      getSettings().getWindowImpl();



        std::shared_ptr<basic_UIModule> UI_module = nullptr;

        switch (UI_module_impl)
        {
        case UIModuleImpl::ImGui:
            UI_module = std::shared_ptr<imgui::UIModule>(&imgui::UIModule::instance(),
                                                         [](imgui::UIModule* _UI_module) -> void
                                                         { });
            break;
        case UIModuleImpl::Qt:
            break;
        case UIModuleImpl::Juce:
            break;
        case UIModuleImpl::GTK_Plus:
            break;
        }

        UI_module->setWindowImpl(window_impl);
        UI_module->setRendererImpl(renderer_impl);
        UI_module->initialize(m_window_ptr);
        if (!UI_module->isInitialized())
            return error::application_error::can_not_setup_UIModule;

        Engine::setApplicationUIModule(std::move(UI_module));

        return std::nullopt;
    }



    auto application::setWindowEventHandlers() noexcept -> void
    {
        m_window_ptr->addEventListener<Events::Resize>(
            [this](const ResizeEventData& _size) -> void
            {
                getSettings().setWidth(_size.width);
                getSettings().setHeight(_size.height);

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



	auto application::start() noexcept -> app_error_t
	{
        auto cfg_error = loadConfig();
        if (cfg_error.has_value())
            return cfg_error;

        auto wind_error = createWindow();
        if (wind_error.has_value())
            return wind_error;

        setWindowEventHandlers();

        auto render_error = setupRenderer();
        if (render_error.has_value())
            return render_error;


        auto UIModule_error = setupUIModule();
        if (UIModule_error.has_value())
            return UIModule_error;

        onStart();

        m_is_closed = false;
        while (!isClosed())
        {
            m_window_ptr->onUpdate();
            onUpdate();
            onDrawUI();
        }

        onClose();

        Engine::getApplicationUIModule()->terminate();
        m_window_ptr->shutdown();
        m_window_context->terminate();

        return std::nullopt;
	}



    auto application::isClosed() const noexcept -> bool
    {
        return m_is_closed;
    }



    auto application::getSettings() noexcept -> application_settings&
    {
        return application_settings::instance();
    }



    auto application::close() noexcept -> void
    {
        m_is_closed = true;
    }



	auto application::onUpdate() noexcept -> void
	{ }
    auto application::onDrawUI() noexcept -> void
    { }
    auto application::onStart() noexcept -> void
    { }
    auto application::onClose() noexcept -> void
    { }



    auto application::onWindowResize() noexcept -> void
    { }
    auto application::onWindowClose() noexcept -> void
    { }
    auto application::onWindowMove() noexcept -> void
    { }
    auto application::onMouseMove() noexcept -> void
    { }
    auto application::onMouseInput() noexcept -> void
    { }
    auto application::onKeyboardInput() noexcept -> void
    { }
}