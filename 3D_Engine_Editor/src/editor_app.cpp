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

#include <engine/render/open_gl/texture2D.hpp>

#include <engine/render/camera.hpp>

#include <engine/modules/imgui/UIModule.hpp>

#include <engine/input/keyboard.hpp>
#include <engine/input/mouse.hpp>

#include <imgui/imgui.h>

#include <iostream>



//-----------------------------------------------------------------------------------------------------------------//   

engine::render::open_gl::GLfloat square_points_colors[] = {
		0.f,  -0.5f, -0.5f,		1.f, 1.f, 0.f,		-1.f, -1.f,
	    0.f,  -0.5f, 0.5f,		0.f, 1.f, 1.f,		-1.f, 2.f,
	    0.f,  0.5f,  0.5f,		1.f, 0.f, 1.f,		2.f, 2.f,
	    0.f,  0.5f,  -0.5f,		0.f, 1.f, 0.f,		2.f, -1.f
};

engine::render::open_gl::GLuint indexes[] = { 0, 1, 2, 2, 3, 0 };

float scale[] = { 1.f, 1.f, 1.f };
float translate[] = { 0.f, 0.f, 0.f };
float rotate = 0.f;



float camera_position[] = { 0.f, 0.f, 0.f };
float camera_rotation[] = { 0.f, 0.f, 0.f };
bool is_perspective_projection = true;

static float bg_color[4] = { 1.f, 0.f, 0.f, 1.f };

static double last_mouse_pos[2] = { 0, 0 };

//-----------------------------------------------------------------------------------------------------------------//

const char* vertex_shader =
		R"(#version 460
		layout(location = 0) in vec3 vertex_poistion;
		layout(location = 1) in vec3 vertex_color;
		layout(location = 2) in vec2 in_texture_coord;
		
		uniform mat4 model_matrix;
		uniform mat4 view_projection_matrix;
		uniform int current_frame;
		
		out vec3 color;
		out vec2 texture_coord_smile;	
		out vec2 texture_coord_quads;		

		void main() {
			color = vertex_color;
			texture_coord_smile = in_texture_coord;
			texture_coord_quads = in_texture_coord + vec2(current_frame / 1500.f, current_frame / 1500.f);
			gl_Position = view_projection_matrix * model_matrix * vec4(vertex_poistion, 1.0);
		})";

const char* fragment_shader =
		R"(#version 460
		in vec3 color;
		in vec2 texture_coord_smile;
		in vec2 texture_coord_quads;

		layout (binding = 0) uniform sampler2D inTextureSmile;
		layout (binding = 1) uniform sampler2D inTextureQuads;

		out vec4 frag_color;

		void main() {
			//frag_color = vec4(color, 1.0);
			frag_color = texture(inTextureSmile, texture_coord_smile) * texture(inTextureQuads, texture_coord_quads);
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

std::unique_ptr<texture2D> textureSmile;
std::unique_ptr<texture2D> textureQuads;



void generateCircle(unsigned char* _data,
					unsigned int _width,
					unsigned int _height,
					unsigned int center_x,
					unsigned int center_y,
					unsigned int radius,
					unsigned char r,
				    unsigned char g,
					unsigned char b)
{
	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) < radius * radius)
			{
				_data[3 * (x + _width * y) + 0] = r;
				_data[3 * (x + _width * y) + 1] = g;
				_data[3 * (x + _width * y) + 2] = b;
			}
		}
	}
}



void generateSmileTexture(unsigned char* _data, std::uint16_t _width, std::uint16_t _height) noexcept
{
	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			_data[3 * (x + _width * y) + 0] = 200;
			_data[3 * (x + _width * y) + 1] = 191;
			_data[3 * (x + _width * y) + 2] = 231;
		}
	}
	generateCircle(_data, _width, _height, _width * 0.5, _height * 0.5, _width * 0.4, 255, 255, 0);

	generateCircle(_data, _width, _height, _width * 0.5, _height * 0.4, _width * 0.2, 0, 0, 0);
	generateCircle(_data, _width, _height, _width * 0.5, _height * 0.45, _width * 0.2, 255, 255, 0);

	generateCircle(_data, _width, _height, _width * 0.35, _height * 0.6, _width * 0.07, 255, 0, 255);
	generateCircle(_data, _width, _height, _width * 0.65, _height * 0.6, _width * 0.07, 0, 0, 255);
}



void generateQuadsTexture(unsigned char* _data, std::uint16_t _width, std::uint16_t _height)
{
	for (size_t x = 0; x < _width; x++)
	{
		for (size_t y = 0; y < _height; y++)
		{
			if (x < _width / 2 && y < _height / 2 || x > _width / 2 && y > _height / 2)
			{
				_data[3 * (x + _width * y) + 0] = 0;
				_data[3 * (x + _width * y) + 1] = 0;
				_data[3 * (x + _width * y) + 2] = 0;
			}
			else
			{
				_data[3 * (x + _width * y) + 0] = 255;
				_data[3 * (x + _width * y) + 1] = 255;
				_data[3 * (x + _width * y) + 2] = 255;
			}
		}
	}
}





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
			ShaderDataType::Float3,
			ShaderDataType::Float2
		};

		points_colors_vbo_ = std::make_unique<vertex_buffer>(square_points_colors, sizeof(square_points_colors),
			points_colors_layout_, vertex_buffer::Usage::Static);

		index_buffer_ = std::make_unique<index_buffer>(indexes, 6, vertex_buffer::Usage::Static);

		VAO_1buffer_ = std::make_unique<vertex_array>();

		VAO_1buffer_->addVertexBuffer(*points_colors_vbo_);
		VAO_1buffer_->setIndexBuffer(*index_buffer_);


		m_window_ptr->setBackgroundColor(0.3f, 0.3f, 0.3f, 1.f);
		const auto& window_bg_color = m_window_ptr->getBackgroundColor();
		bg_color[0] = window_bg_color[0];
		bg_color[1] = window_bg_color[1];
		bg_color[2] = window_bg_color[2];
		bg_color[3] = window_bg_color[3];


		unsigned int width = 1000;
		unsigned int height = 1000;

		auto* data = new unsigned char[width * height * 3];
		generateSmileTexture(data, width, height);

		textureSmile = std::make_unique<texture2D>();
		textureQuads = std::make_unique<texture2D>();

		TextureParamsStorage tex_params_storage_ = { Wrap::Repeat, Wrap::Repeat,
													 Filter::Linear, Filter::Linear };

		textureSmile->setData(data, width, height);
		textureSmile->setParametrs(tex_params_storage_);
		textureSmile->bind(0);

		generateQuadsTexture(data, width, height);
		textureQuads->setData(data, width, height);
		textureQuads->setParametrs(tex_params_storage_);
		textureQuads->bind(1);

		delete[] data;



		LOG_INFO("'{0}' application started, size: {1}x{2}", m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
	}



	void editor_app::setEventListeners() noexcept
	{
		m_window_ptr->addEventListener<Events::Resize>(
			[this](const ResizeEventData& _size) -> void
			{
				renderer::setViewport(_size.width, _size.height);
			});

		m_window_ptr->addEventListener<Events::Close>(
			[this]() -> void
			{
				close();
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
				if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_ESCAPE))
				{
					close();
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

		static int currnet_frame = 0;
		shader_program_->setMatrix4f("model_matrix", model_matrix);
		shader_program_->setInt1("current_frame", currnet_frame++);
		m_camera->setProjectionMode(is_perspective_projection ? camera::Projection::Perspective : camera::Projection::Orthographic);

		shader_program_->setMatrix4f("view_projection_matrix", m_camera->getViewProjectionMatrix());

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
		
		//-----------------------------------------------------------------------------------------------------------------//

		auto current_mouse_pos = m_window_ptr->getCurrentCursorPosition();

		if (engine::input::mouse::isButtonPressed(engine::input::MouseButton::MOUSE_BUTTON_LEFT))
		{
			
			rotation_delta.z -= (current_mouse_pos.x - last_mouse_pos[0]) / 10;
			rotation_delta.y += (current_mouse_pos.y - last_mouse_pos[1]) / 10;	
		}
		if (engine::input::mouse::isButtonPressed(engine::input::MouseButton::MOUSE_BUTTON_RIGHT))
		{
			movement_delta.y += (current_mouse_pos.x - last_mouse_pos[0]) / 100;
			m_camera->moveWorldUp(-(current_mouse_pos.y - last_mouse_pos[1]) / 100);
		}

		last_mouse_pos[0] = current_mouse_pos.x;
		last_mouse_pos[1] = current_mouse_pos.y;

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