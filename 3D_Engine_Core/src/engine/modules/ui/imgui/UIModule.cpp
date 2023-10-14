#include <engine/modules/ui/imgui/UIModule.hpp>

#include <engine/logging/log.hpp>

#include <engine/window/glfw/glfw_window.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>



namespace engine::modules::ui::imgui
{
    UIModule& UIModule::instance() noexcept
    {
        static UIModule instance;
        return instance;
    }



    void UIModule::setupImGuiConfig() const noexcept
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;
    }



	void UIModule::initialize(const window_ptr& _window_ptr) noexcept
	{
        setupImGuiConfig();

        switch (m_render_impl)
        {
        case engine::render::RendererImpl::OpenGL:
            ImGui_ImplOpenGL3_Init();
            break;
        case engine::render::RendererImpl::Vulkan:
            break;
        case engine::render::RendererImpl::DirectX:
            break;
        case engine::render::RendererImpl::Direct3D:
            break;
        }

        switch (m_window_impl)
        {
        case engine::window::WindowImpl::GLFW:
            if (m_render_impl == RendererImpl::OpenGL)
            {
                window::glfw::glfw_window* glfw_window = dynamic_cast<window::glfw::glfw_window*>(_window_ptr.get());
                if (glfw_window != nullptr)
                    ImGui_ImplGlfw_InitForOpenGL(glfw_window->getRawGlfwPtr(), true);
                else
                    LOG_ERROR("[ImGui UIModule ERROR] Can't cast basic_window to glfw window.");
            }
            break;
        case engine::window::WindowImpl::SDL:
            break;
        case engine::window::WindowImpl::SFML:
            break;
        }

        m_is_inited = true;
	}



	void UIModule::terminate() noexcept
	{
        switch (m_render_impl)
        {
        case engine::render::RendererImpl::OpenGL:
            ImGui_ImplOpenGL3_Shutdown();
            break;
        case engine::render::RendererImpl::Vulkan:
            break;
        case engine::render::RendererImpl::DirectX:
            break;
        case engine::render::RendererImpl::Direct3D:
            break;
        }

        switch (m_window_impl)
        {
        case engine::window::WindowImpl::GLFW:
            ImGui_ImplGlfw_Shutdown();
            break;
        case engine::window::WindowImpl::SDL:
            break;
        case engine::window::WindowImpl::SFML:
            break;
        }

		ImGui::DestroyContext();

        m_is_inited = false;
	}



	void UIModule::onUIDrawBegin() const noexcept
	{
        switch (m_render_impl)
        {
        case engine::render::RendererImpl::OpenGL:
            ImGui_ImplOpenGL3_NewFrame();
            break;
        case engine::render::RendererImpl::Vulkan:
            break;
        case engine::render::RendererImpl::DirectX:
            break;
        case engine::render::RendererImpl::Direct3D:
            break;
        }

        switch (m_window_impl)
        {
        case engine::window::WindowImpl::GLFW:
            ImGui_ImplGlfw_NewFrame();
            break;
        case engine::window::WindowImpl::SDL:
            break;
        case engine::window::WindowImpl::SFML:
            break;
        }
		
        ImGui::NewFrame();
	}



	void UIModule::onUIDrawEnd() const noexcept
	{
		ImGui::Render();
		
        if (m_render_impl == RendererImpl::OpenGL && m_window_impl == WindowImpl::GLFW)
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }
	}



    bool UIModule::isMouseOnUI() const noexcept
    {
        return ImGui::GetIO().WantCaptureMouse;
    }



    void UIModule::begin(const std::string_view& _title) const noexcept
    {
        ImGui::Begin(_title.data());
    }



    void UIModule::end() const noexcept
    {
        ImGui::End();
    }



    isClicked UIModule::putColorEdit4(const std::string_view& _title, glm::vec4& _color) const noexcept
    {
        return ImGui::ColorEdit4(_title.data(), &_color[0]);
    }



    isClicked UIModule::putSliderFloat(const std::string_view& _title, float& _value, float _min_val, float _max_val) const noexcept
    {
        return ImGui::SliderFloat(_title.data(), &_value, _min_val, _max_val);
    }



    isClicked UIModule::putSliderFloat2(const std::string_view& _title, glm::vec2& _value, float _min_val, float _max_val) const noexcept
    {
        return ImGui::SliderFloat2(_title.data(), &_value[0], _min_val, _max_val);
    }



    isClicked UIModule::putSliderFloat3(const std::string_view& _title, glm::vec3& _value, float _min_val, float _max_val) const noexcept
    {
        return ImGui::SliderFloat3(_title.data(), &_value[0], _min_val, _max_val);
    }



    isClicked UIModule::putSliderFloat4(const std::string_view& _title, glm::vec4& _value, float _min_val, float _max_val) const noexcept
    {
        return ImGui::SliderFloat4(_title.data(), &_value[0], _min_val, _max_val);
    }



    isClicked UIModule::putCheckbox(const std::string_view& _title, bool& _value) const noexcept
    {
        return ImGui::Checkbox(_title.data(), &_value);
    }



    isClicked UIModule::putRadioButton(const std::string_view& _title, int& _versions, int _version) const noexcept
    {
        return ImGui::RadioButton(_title.data(), &_versions, _version);
    }



    void UIModule::separate() const noexcept
    {
        ImGui::Separator();
    }


    void UIModule::newLine() const noexcept
    {
        ImGui::NewLine();
    }



    void UIModule::sameLine() const noexcept
    {
        ImGui::SameLine();
    }



    void UIModule::createDockSpace() const noexcept
    {
        static bool is_open = false;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
        }


        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", &is_open, window_flags);

        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End();
    }
}