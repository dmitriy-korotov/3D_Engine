#include <editor_app.hpp>

#include <engine/logging/log.hpp>

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
#include <engine/input/mouse.hpp>

#include <imgui/imgui.h>

#include <iostream>



//-----------------------------------------------------------------------------------------------------------------//   

engine::render::open_gl::GLfloat square_points_colors[] = {
		0.f,  -0.5f, -0.5f,		1.f, 1.f, 0.f,
	    0.f,  -0.5f, 0.5f,		0.f, 1.f, 1.f,
	    0.f,  0.5f,  0.5f,		1.f, 0.f, 1.f,
	    0.f,  0.5f,  -0.5f,		0.f, 1.f, 0.f
};

engine::render::open_gl::GLuint indexes[] = { 0, 1, 2, 2, 3, 0 };

float scale[] = { 1.f, 1.f, 1.f };
float translate[] = { 0.f, 0.f, 0.f };
float rotate = 0.f;



float camera_position[] = { 0.f, 0.f, 0.f };
float camera_rotation[] = { 0.f, 0.f, 0.f };
bool is_perspective_projection = true;

static float bg_color[4] = { 1.f, 0.f, 0.f, 1.f };

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
		, m_camera(std::make_unique<engine::render::camera>(glm::vec3(-3.f, 0.f, 0.f)))
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

		const auto& window_bg_color = m_window_ptr->getBackgroundColor();
		bg_color[0] = window_bg_color[0];
		bg_color[1] = window_bg_color[1];
		bg_color[2] = window_bg_color[2];
		bg_color[3] = window_bg_color[3];



		LOG_INFO("'{0}' application started, size: {1}x{2}", m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
	}



	void editor_app::setEventListeners() const noexcept
	{
		m_window_ptr->addEventListener<Events::Resize>(
			[this](const ResizeEventData& _size) -> void
			{
				renderer::setViewport(_size.width, _size.height);
			});

		m_window_ptr->addEventListener<Events::Close>(
			[this]() -> void
			{
				s_is_closed = true;
			});
		m_window_ptr->addEventListener<Events::KeyboardInput>(
			[this](const KeyboardInputEventData& _keyboard_intput_data) -> void
			{
				if (_keyboard_intput_data.key < engine::input::Key::KEY_Z)
				{
					if (_keyboard_intput_data.action == engine::input::Action::Pressed)
					{
						LOG_INFO("[Keyboard Input] Pressed key: {0}", static_cast<char>(_keyboard_intput_data.key));
					}
					else if (_keyboard_intput_data.action == engine::input::Action::Released)
					{
						LOG_INFO("[Keyboard Input] Released key: {0}", static_cast<char>(_keyboard_intput_data.key));
					}
					else
					{
						LOG_INFO("[Keyboard Input] Repeted press key: {0}", static_cast<char>(_keyboard_intput_data.key));
					}
				}
			});
		m_window_ptr->addEventListener<Events::MouseInput>(
			[this](const MouseInputEventData& _mouse_input_data) -> void
			{

			});
	}



	void editor_app::onUpdate() noexcept
	{ 
		renderer::setClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
		renderer::clear(renderer::Mask::ColorBuffer);



		shader_program_->bind();
		VAO_1buffer_->bind();
		renderer::draw(*VAO_1buffer_);



		glm::mat4 model_matrix(1);

		shader_program_->setMatrix4f("model_matrix", model_matrix);
		m_camera->setProjectionMode(is_perspective_projection ? camera::Projection::Perspective : camera::Projection::Orthographic);

		shader_program_->setMatrix4f("view_projection_matrix", m_camera->getViewProjectionMatrix());
		
		//-----------------------------------------------------------------------------------------------------------------//

		if (engine::input::mouse::isButtonPressed(engine::input::MouseButton::MOUSE_BUTTON_LEFT))

		//-----------------------------------------------------------------------------------------------------------------//
		
		glm::vec3 movement_delta = { 0.f, 0.f, 0.f };
		glm::vec3 rotation_delta = { 0.f, 0.f, 0.f };

		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_W))
		{
			movement_delta.x += 0.005f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_S))
		{
			movement_delta.x -= 0.005f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_D))
		{
			movement_delta.y += 0.005f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_A))
		{
			movement_delta.y -= 0.005f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_E))
		{
			movement_delta.z += 0.005f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_Q))
		{
			movement_delta.z -= 0.005f;
		}



		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_UP))
		{
			rotation_delta.y -= 0.1f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_DOWN))
		{
			rotation_delta.y += 0.1f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_RIGHT))
		{
			rotation_delta.z -= 0.1f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_LEFT))
		{
			rotation_delta.z += 0.1f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_KP_6))
		{
			rotation_delta.x -= 0.1f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_KP_4))
		{
			rotation_delta.x += 0.1f;
		}

		m_camera->moveAndRotate(movement_delta, rotation_delta);
		
		//-----------------------------------------------------------------------------------------------------------------//

		drawUI();
	}



	void editor_app::drawUI() noexcept
	{ 
		camera_position[0] = m_camera->getPosition().x;
		camera_position[1] = m_camera->getPosition().y;
		camera_position[2] = m_camera->getPosition().z;

		camera_rotation[0] = m_camera->getRotation().x;
		camera_rotation[1] = m_camera->getRotation().y;
		camera_rotation[2] = m_camera->getRotation().z;

		UIModule::onUIDrawBegin_GlfwWindow_OpenGLRenderer();

		UIModule::createDockSpace();

		ImGui::Begin("BG Color");
		ImGui::ColorEdit4("Background color", bg_color);
		ImGui::End();

		ImGui::Begin("Camera");
		if (ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f))
		{
			m_camera->setPosition(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
		}
		if (ImGui::SliderFloat3("Camera rotation", camera_rotation, -360.f, 360.f))
		{
			m_camera->setRotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		}
		ImGui::Checkbox("Perspective projection", &is_perspective_projection);
		ImGui::End();

		UIModule::onUIDrawEnd_GlfwWindow_OpenGLRenderer();
	}



	editor_app::~editor_app()
	{
		UIModule::onGLfwWindowShutdown_OpenGLRenderer();
		LOG_INFO("'{0}' application closed, size: {1}x{2}", m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
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