#include <editor_app.hpp>

#include <engine/window/glfw/glfw_window.hpp>
#include <engine/window/glfw/events_data.hpp>

#include <engine/render/open_gl/renderer_open_gl.hpp>
#include <engine/render/open_gl/gl_types.hpp>

#include <engine/render/open_gl/shader_program.hpp>
#include <engine/render/open_gl/index_buffer.hpp>
#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/vertex_array.hpp>

#include <engine/render/camera.hpp>

#include <engine/modules/imgui/UIModule.hpp>

#include <engine/input/keyboard.hpp>

#include <imgui/imgui.h>

#include <iostream>



//-----------------------------------------------------------------------------------------------------------------//   

engine::render::open_gl::GLfloat square_points_colors[] = {
        -0.5f, -0.5f, 0.f,		1.f, 1.f, 0.f,
        -0.5f, 0.5f, 0.f,		0.f, 1.f, 1.f,
        0.5f, 0.5f, 0.f,		1.f, 0.f, 1.f,
        0.5f, -0.5f, 0.f,		0.f, 1.f, 0.f
};

engine::render::open_gl::GLuint indexes[] = { 0, 1, 2, 2, 3, 0 };

float scale[] = { 1.f, 1.f, 1.f };
float translate[] = { 0.f, 0.f, 0.f };
float rotate = 0.f;



float camera_position[] = { 0.f, 0.f, 0.f };
float camera_rotation[] = { 0.f, 0.f, 0.f };
bool is_perspective_projection = true;

//-----------------------------------------------------------------------------------------------------------------//

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

//-----------------------------------------------------------------------------------------------------------------//

using namespace engine::window::glfw;
using namespace engine::render::open_gl;
using namespace engine::render;
using namespace engine::modules::imgui;

//-----------------------------------------------------------------------------------------------------------------//

std::unique_ptr<shader_program> shader_program_;

std::unique_ptr<vertex_buffer> points_colors_vbo_;
std::unique_ptr<index_buffer> index_buffer_;

std::unique_ptr<vertex_array> VAO_1buffer_;



namespace editor
{
	editor_app::editor_app(uint16_t _width, uint16_t _height,
		const std::string_view& _editor_name)
		: application(_width, _height, _editor_name)
		, m_camera(std::make_unique<engine::render::camera>())
	{
		setEventListeners();
		if (!renderer::init_with_glfw())
		{
			std::cerr << "[Editor ERROR] Can't init OpenGL with Glfw." << std::endl; 
		}
		UIModule::onGlfwWindowCreate_OpenGLRenderer(m_window_ptr);



		shader_program_ = std::make_unique<shader_program>(vertex_shader, fragment_shader);

		buffer_layout points_colors_layout_
		{
			ShaderDataType::Float3,
			ShaderDataType::Float3
		};

		points_colors_vbo_ = std::make_unique<vertex_buffer>(square_points_colors, sizeof(square_points_colors),
			points_colors_layout_, vertex_buffer::Usage::Static);

		index_buffer_ = std::make_unique<index_buffer>(indexes, 6, vertex_buffer::Usage::Static);

		VAO_1buffer_ = std::make_unique<vertex_array>();

		VAO_1buffer_->addVertexBuffer(*points_colors_vbo_);
		VAO_1buffer_->setIndexBuffer(*index_buffer_);
	}



	void editor_app::onUpdate() noexcept
	{ 
		window::bg_color& bg_color = m_window_ptr->getBackgroundColor();
		renderer::setClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
		renderer::clear(renderer::Mask::ColorBuffer);



		shader_program_->bind();
		VAO_1buffer_->bind();
		renderer::draw(*VAO_1buffer_);



		glm::mat4 model_matrix(1);

		shader_program_->setMatrix4f("model_matrix", model_matrix);

		m_camera->setPositionAndRotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
										 glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		m_camera->setProjectionMode(is_perspective_projection ? camera::Projection::Perspective : camera::Projection::Orthographic);

		shader_program_->setMatrix4f("view_projection_matrix", m_camera->getViewProjectionMatrix());



		drawUI();
	}



	editor_app::~editor_app()
	{
		UIModule::onGLfwWindowShutdown_OpenGLRenderer();
	}



	void editor_app::setEventListeners() const noexcept
	{
		m_window_ptr->addEventListener<Events::Resize>(
			[](const ResizeEventData& _size) -> void
			{
				renderer::setViewport(_size.width, _size.height);
			});

		m_window_ptr->addEventListener<Events::Close>(
			[this]() -> void
			{
				s_is_closed = true;
			});
		m_window_ptr->addEventListener<Events::KeyboardInput>(
			[](const KeyboardInputEventData& _keyboard_intput_data) -> void
			{
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_W))
				{
					camera_position[2] -= 0.05f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_S))
				{
					camera_position[2] += 0.05f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_D))
				{
					camera_position[0] += 0.05f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_A))
				{
					camera_position[0] -= 0.05f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_E))
				{
					camera_position[1] += 0.05f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_Q))
				{
					camera_position[1] -= 0.05f;
				}



				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_UP))
				{
					camera_rotation[0] += 1.f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_DOWN))
				{
					camera_rotation[0] -= 1.f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_RIGHT))
				{
					camera_rotation[1] -= 1.f;
				}
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_LEFT))
				{
					camera_rotation[1] += 1.f;
				}
			});
	}



	void editor_app::drawUI() noexcept
	{ 
		window::bg_color& bg_color = m_window_ptr->getBackgroundColor();

		UIModule::onUIDrawBegin_GlfwWindow_OpenGLRenderer();

		UIModule::createDockSpace();

		ImGui::Begin("BG Color");
		ImGui::ColorEdit4("Background color", bg_color.data());
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, -360.f, 360.f);
		ImGui::Checkbox("Perspective projection", &is_perspective_projection);
		ImGui::End();

		UIModule::onUIDrawEnd_GlfwWindow_OpenGLRenderer();
	}
}



/*
//-----------------------------------------------------------------------------------------------------------------//   

//-----------------------------------------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------------------------------------//





static bool is_one_buffer = true;
if (is_one_buffer)
{
	
}
else
{
	VAO_2buffers_->bind();
	renderer::draw(*VAO_2buffers_);
}


float rad_angle = glm::radians(rotate);

glm::mat4 rotate_matrix(glm::cos(rad_angle), glm::sin(rad_angle), 0, 0,
						-glm::sin(rad_angle), glm::cos(rad_angle), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);

glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;




ui::ImGuiModule::onUIDrawBegin();

bool open = true;
ui::ImGuiModule::ShowExampleAppDockSpace(&open);
ImGui::ShowDemoWindow();



ui::ImGuiModule::onUIDrawEnd();

window::onUpdate();
*/