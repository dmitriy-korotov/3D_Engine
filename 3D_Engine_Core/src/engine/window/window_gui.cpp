#include <engine/window/window_gui.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine
{
	window_gui::window_gui(const std::string_view& _title)
			: glfw_window(_title)
	{ }



	std::optional<error::window_error> window_gui::create(std::uint16_t _width, std::uint16_t _height) noexcept
	{
		auto result_ = glfw_window::create(_width, _height);
		if (result_.has_value())
		{
			LOG_CRITICAL("Can't create window_glfw '{0}' in window_gui.", m_window_data_.title);
			return error::window_error::can_not_create;
		}

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			LOG_CRITICAL("Can't load glad.");
			return error::window_error::can_not_create;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(m_window_ptr_, true);

		return std::nullopt;
	}



	void window_gui::onUpdate() noexcept
	{
		glClearColor(m_bg_color_[0], m_bg_color_[1], m_bg_color_[2], m_bg_color_[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGuiIO& io_ = ImGui::GetIO();
		io_.DisplaySize.x = static_cast<float>(getWidth());
		io_.DisplaySize.y = static_cast<float>(getHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("BG Color Editor");
		ImGui::ColorEdit4("Background color", m_bg_color_.data());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfw_window::onUpdate();
	}
}