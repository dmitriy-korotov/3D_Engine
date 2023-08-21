#include <engine/window/window_gui.hpp>

#include <engine/render/open_gl/shader_program.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



GLfloat points[] = {
		-0.5f, -0.5f, 0.f,
		0.f, 0.5f, 0.f,
		0.5f, -0.5f, 0.f
};

GLfloat colors[] = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_poistion;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"	color = vertex_color;"
"	gl_Position = vec4(vertex_poistion, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"	frag_color = vec4(color, 1.0);"
"}";

std::unique_ptr<engine::render::shader_program> shader_program_;
GLuint VAO_ = 0;



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

		shader_program_ = std::make_unique<engine::render::shader_program>(vertex_shader, fragment_shader);

		GLuint points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		glGenVertexArrays(1, &VAO_);
		glBindVertexArray(VAO_);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		return std::nullopt;
	}



	void window_gui::onUpdate() noexcept
	{
		glClearColor(m_bg_color_[0], m_bg_color_[1], m_bg_color_[2], m_bg_color_[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader_program_->bind();
		glBindVertexArray(VAO_);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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