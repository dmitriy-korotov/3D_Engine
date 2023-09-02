#include <engine/window/window_gui.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/open_gl/shader_program.hpp>
#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/index_buffer.hpp>
#include <engine/render/open_gl/vertex_array.hpp>
#include <engine/render/open_gl/buffer_layout.hpp>

#include <engine/render/camera.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>

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



float scale[] = { 1.f, 1.f, 1.f };
float translate[] = { 0.f, 0.f, 0.f };
float rotate = 0.f;

float camera_position[] = { 0.f, 0.f, 0.f };
float camera_rotation[] = { 0.f, 0.f, 0.f };
bool is_perspective_projection = false;



std::unique_ptr<engine::render::camera> camera;



const char* vertex_shader =
		R"(#version 460
		layout(location = 0) in vec3 vertex_poistion;
		layout(location = 1) in vec3 vertex_color;
		uniform mat4 model_matrix;
		uniform mat4 view_projection_matrix;
		out vec3 color;
		void main() {
			color = vertex_color;
			gl_Position = view_projection_matrix * model_matrix * vec4(vertex_poistion, 1.0);
		})";

const char* fragment_shader =
		R"(#version 460
		in vec3 color;
		out vec4 frag_color;
		void main() {
			frag_color = vec4(color, 1.0);
		})";





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

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(m_window_ptr, true);

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



		camera = std::make_unique<render::camera>();



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

		glm::mat4 scale_matrix(scale[0],	    0,		  0,		 0,
							   0,		 scale[1],		  0,		 0,
							   0,				0,	scale[2],		 0,
							   0,			    0,		  0,		 1);

		glm::mat4 translate_matrix(1,			0,		  0,		 0,
								   0,			1,		  0,		 0,
								   0,			0,		  1,		 0,
								   translate[0], translate[1], translate[2], 1);

		float rad_angle = glm::radians(rotate);

		glm::mat4 rotate_matrix(glm::cos(rad_angle), glm::sin(rad_angle), 0, 0,
							    -glm::sin(rad_angle), glm::cos(rad_angle), 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);

		glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;

		shader_program_->setMatrix4f("model_matrix", model_matrix);

		camera->setPositionAndRotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
									   glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		camera->setProjectionMode(is_perspective_projection ? render::camera::Projection::Perspective : render::camera::Projection::Orthographic);

		shader_program_->setMatrix4f("view_projection_matrix", camera->getViewProjectionMatrix());



		ImGuiIO& io_ = ImGui::GetIO();
		io_.DisplaySize.x = static_cast<float>(getWidth());
		io_.DisplaySize.y = static_cast<float>(getHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("BG Color Editor");
		ImGui::ColorEdit4("Background color", m_bg_color_.data());
		ImGui::Checkbox("One buffer rendering", &is_one_buffer);
		ImGui::SliderFloat3("Scale", scale, 0.f, 2.f);
		ImGui::SliderFloat3("Translate", translate, -1.f, 1.f);
		ImGui::SliderFloat("Rotate", &rotate, 0.f, 360.f);
		ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f);
		ImGui::Checkbox("Perspective projection", &is_perspective_projection);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfw_window::onUpdate();
	}
}