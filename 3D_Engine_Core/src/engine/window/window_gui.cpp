#include <engine/window/window_gui.hpp>

#include <engine/render/open_gl/shader_program.hpp>
#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/index_buffer.hpp>
#include <engine/render/open_gl/vertex_array.hpp>
#include <engine/render/open_gl/buffer_layout.hpp>

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

GLfloat points_colors[] = {
		-0.5f, -0.5f, 0.f,		1.f, 1.f, 0.f,
		0.f, 0.5f, 0.f,			0.f, 1.f, 1.f,
		0.5f, -0.5f, 0.f,		1.f, 0.f, 1.f
};

GLfloat square_points_colors[] = {
		-0.5f, -0.5f, 0.f,		1.f, 1.f, 0.f,
		-0.5f, 0.5f, 0.f,		0.f, 1.f, 1.f,
		0.5f, 0.5f, 0.f,		1.f, 0.f, 1.f,
		0.5f, -0.5f, 0.f,		0.f, 1.f, 0.f
};

GLuint indexes[] = { 0, 1, 2, 2, 3, 0 };



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

std::unique_ptr<engine::render::vertex_buffer> points_vbo_;
std::unique_ptr<engine::render::vertex_buffer> colors_vbo_;
std::unique_ptr<engine::render::vertex_buffer> points_colors_vbo_;

std::unique_ptr<engine::render::index_buffer> index_buffer_;

std::unique_ptr<engine::render::vertex_array> VAO_1buffer_;
std::unique_ptr<engine::render::vertex_array> VAO_2buffers_;



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


		render::buffer_layout points_layout_
		{
			render::ShaderDataType::Float3
		};
		points_vbo_ = std::make_unique<render::vertex_buffer>(points, sizeof(points), points_layout_,
															  render::vertex_buffer::Usage::Static);

		render::buffer_layout colors_layout_
		{
			render::ShaderDataType::Float3
		};
		colors_vbo_ = std::make_unique<render::vertex_buffer>(colors, sizeof(colors), colors_layout_,
						 									  render::vertex_buffer::Usage::Static);

		VAO_2buffers_ = std::make_unique<render::vertex_array>();

		VAO_2buffers_->addVertexBuffer(*points_vbo_);
		VAO_2buffers_->addVertexBuffer(*colors_vbo_);



		render::buffer_layout points_colors_layout_
		{
			render::ShaderDataType::Float3,
			render::ShaderDataType::Float3
		};

		points_colors_vbo_ = std::make_unique<render::vertex_buffer>(square_points_colors, sizeof(square_points_colors),
																	 points_colors_layout_, render::vertex_buffer::Usage::Static);

		index_buffer_ = std::make_unique<render::index_buffer>(indexes, 6, render::vertex_buffer::Usage::Static);

		VAO_1buffer_ = std::make_unique<render::vertex_array>();

		VAO_1buffer_->addVertexBuffer(*points_colors_vbo_);
		VAO_1buffer_->setIndexBuffer(*index_buffer_);

		return std::nullopt;
	}



	void window_gui::onUpdate() noexcept
	{
		glClearColor(m_bg_color_[0], m_bg_color_[1], m_bg_color_[2], m_bg_color_[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader_program_->bind();
		
		static bool is_one_buffer = true;
		if (is_one_buffer)
		{
			VAO_1buffer_->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			VAO_2buffers_->bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		

		ImGuiIO& io_ = ImGui::GetIO();
		io_.DisplaySize.x = static_cast<float>(getWidth());
		io_.DisplaySize.y = static_cast<float>(getHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("BG Color Editor");
		ImGui::ColorEdit4("Background color", m_bg_color_.data());
		ImGui::Checkbox("One buffer rendering", &is_one_buffer);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfw_window::onUpdate();
	}
}