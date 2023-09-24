/*#include <editor_app.hpp>

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

#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include <engine/util/file_reader.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/components/transform_component.hpp>
#include <engine/ecs/systems/systems_manager.hpp>
#include <engine/ecs/systems/render_system.hpp>

#include <engine/models/cube.hpp>


#include <iostream>

#include <complex>



//-----------------------------------------------------------------------------------------------------------------//   

engine::render::open_gl::GLfloat square_points[] = {
		0.f,  -0.5f,  -0.5f,		1.f, 0.f, 0.f,		1.f, 0.f,
	    0.f,  -0.5f,  0.5f,			1.f, 0.f, 0.f,		1.f, 1.f,		// far plane
	    0.f,  0.5f,   0.5f,			1.f, 0.f, 0.f,		0.f, 1.f,
	    0.f,  0.5f,   -0.5f,		1.f, 0.f, 0.f,		0.f, 0.f,

		-1.f,  -0.5f,  -0.5f,		-1.f, 0.f, 0.f,		1.f, 0.f,
		-1.f,  -0.5f,  0.5f,		-1.f, 0.f, 0.f,		1.f, 1.f,		// near plain
		-1.f,  0.5f,   0.5f,		-1.f, 0.f, 0.f,		0.f, 1.f,
		-1.f,  0.5f,   -0.5f,		-1.f, 0.f, 0.f,		0.f, 0.f,

		-1.f,  -0.5f,  -0.5f,		0.f, -1.f, 0.f,		0.f, 0.f,
		-1.f,  -0.5f,  0.5f,		0.f, -1.f, 0.f,		0.f, 1.f,		// right plane
		0.f,  -0.5f,  0.5f,			0.f, -1.f, 0.f,		1.f, 1.f,
		0.f,  -0.5f,  -0.5f,		0.f, -1.f, 0.f,		1.f, 0.f,

		-1.f,  0.5f,  -0.5f,		0.f, 1.f, 0.f,		1.f, 0.f,
		-1.f,  0.5f,  0.5f,			0.f, 1.f, 0.f,		1.f, 1.f,		// left plane
		0.f,   0.5f,  0.5f,			0.f, 1.f, 0.f,		0.f, 1.f,
		0.f,   0.5f,  -0.5f,		0.f, 1.f, 0.f,		0.f, 0.f,

		-1.f,  -0.5f,  -0.5f,		0.f, 0.f, -1.f,		1.f, 1.f,
		-1.f,  0.5f,   -0.5f,		0.f, 0.f, -1.f,		0.f, 1.f,		// bottom plane
		0.f,   0.5f,   -0.5f,		0.f, 0.f, -1.f,		0.f, 0.f,
		0.f,   -0.5f,  -0.5f,		0.f, 0.f, -1.f,		1.f, 0.f,

		-1.f,  -0.5f,  0.5f,		0.f, 0.f, 1.f,		1.f, 0.f,
		-1.f,  0.5f,   0.5f,		0.f, 0.f, 1.f,		0.f, 0.f,		// top plane
		0.f,   0.5f,   0.5f,		0.f, 0.f, 1.f,		0.f, 1.f,
		0.f,   -0.5f,  0.5f,		0.f, 0.f, 1.f,		1.f, 1.f
};

engine::render::open_gl::GLuint indexes[] = {
	0, 1, 2, 2, 3, 0,			// front
	4, 5, 6, 6, 7, 4,			// back
	8, 9, 10, 10, 8, 11,		// right
	15, 14, 13, 13, 15, 12,		// left
	18, 17, 16, 16, 18, 19,		// bottom
	21, 22, 23, 23, 21, 20		// top
	
};

float scale[] = { 1.f, 1.f, 1.f };
float translate[] = { 0.f, 0.f, 0.f };
float rotate = 0.f;



float camera_position[] = { 0.f, 0.f, 0.f };
float camera_rotation[] = { 0.f, 0.f, 0.f };
bool is_perspective_projection = true;

float field_of_view = 0.f;
float near_plane = 0.f;
float far_plane = 0.f;

static float bg_color[4] = { 1.f, 0.f, 0.f, 1.f };

static double last_mouse_pos[2] = { 0, 0 };

//-----------------------------------------------------------------------------------------------------------------//

float ambient_factor = 0.1f;
float diffuse_factor = 1.f;
float specular_factor = 0.5f;
float shiniess = 32.f;
float source_light_color[] = { 1.f, 1.f, 1.f, 1.f };

//-----------------------------------------------------------------------------------------------------------------//

const char* source_light_vertex_shader =
		R"(#version 460
		layout(location = 0) in vec3 vertex_poistion;
		layout(location = 1) in vec3 vertex_normal;
		layout(location = 2) in vec2 texture_coords;
		
		uniform mat4 mvp_matrix;

		void main() {
			gl_Position = mvp_matrix * vec4(vertex_poistion * 0.25, 1.0);
		})";

const char* source_light_fragment_shader =
		R"(#version 460
		uniform vec3 source_light_color;
		
		out vec4 frag_color;

		void main() {
			frag_color = vec4(source_light_color, 1.0);
		})";

//-----------------------------------------------------------------------------------------------------------------//

using namespace engine::window::glfw;
using namespace engine::render::open_gl;
using namespace engine::render;
using namespace engine::modules::imgui;

//-----------------------------------------------------------------------------------------------------------------//

std::unique_ptr<shader_program> shader_program_;
std::unique_ptr<shader_program> source_light_shader_program_;

std::unique_ptr<vertex_buffer> points_colors_vbo_;
std::unique_ptr<index_buffer> index_buffer_;

std::unique_ptr<vertex_array> VAO_1buffer_;

std::unique_ptr<texture2D> textureSmile;
std::unique_ptr<texture2D> textureQuads;
std::unique_ptr<texture2D> textureMandelbrotSet;



std::vector<glm::vec3> positions = { glm::vec3(-2.f, 1.f, 2.f),
									 glm::vec3(3.f, 0.f, -2.f),
									 glm::vec3(3.f, 3.f, 2.f),
									 glm::vec3(-3.f, 1.f, 0.f),
									 glm::vec3(2.f, -2.f, -2.f),
									 glm::vec3(0.f, -2.f, 1.f) };



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




void generateMandelbrotSet(unsigned char* _data, std::uint16_t _size) noexcept
{
	uint16_t _P = _size / 2;
	double scale = _P / 2;
	size_t n_iter = 100;

	for (int x = -_P; x < _P; x++)
	{
		for (int y = -_P; y < _P; y++)
		{
			double a = x / scale;
			double b = y / scale;
			std::complex c(a, b);
			std::complex<double> z(0);
			size_t n = 0;

			for (n = 0; n < n_iter; n++)
			{
				z = z * z + c;
				if (std::abs(z) > 2)
				{
					break;
				}
			}

			if (n == n_iter)
			{
				_data[3 * ((x + _P) + _size * (y + _P)) + 0] = 0;
				_data[3 * ((x + _P) + _size * (y + _P)) + 1] = 0;
				_data[3 * ((x + _P) + _size * (y + _P)) + 2] = 0;
			}
			else
			{
				_data[3 * ((x + _P) + _size * (y + _P)) + 0] = (n % 2) * 32 + 128;
				_data[3 * ((x + _P) + _size * (y + _P)) + 1] = (n % 4) * 64;
				_data[3 * ((x + _P) + _size * (y + _P)) + 2] = (n % 2) * 16 + 128;
			}
		}
	}
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
		: application(_width, _height, _editor_name, false)
		, m_camera(std::make_unique<engine::render::camera>(glm::vec3(-3.f, 0.f, 0.f)))
	{

		m_window_ptr->setupIcon("C:\\Users\\User\\MyProjects\\3D_Engine\\res\\icon\\pngwing.png");

		m_camera->setViewPortSize(m_window_ptr->getWidth(), m_window_ptr->getHeight());
		field_of_view = m_camera->getFieldOfView();
		near_plane = m_camera->getNearPlane();
		far_plane = m_camera->getFarPlane();

		setEventListeners();
		if (!renderer::init_with_glfw())
		{
			std::cerr << "[Editor ERROR] Can't init OpenGL with Glfw." << std::endl; 
		}
		UIModule::onGlfwWindowCreate_OpenGLRenderer(m_window_ptr);

		renderer::enableDepthTest();

		engine::util::file_reader vertex_shader_reader("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\shaders\\VertexShader.glsl");
		std::string& vertex_shader_surces = vertex_shader_reader.getData();
		engine::util::file_reader fragment_shader_reader("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\shaders\\FragmentShader.glsl");
		std::string& fragment_shader_surces = fragment_shader_reader.getData();
		shader_program_ = std::make_unique<shader_program>(vertex_shader_surces, fragment_shader_surces);
		source_light_shader_program_ = std::make_unique<shader_program>(source_light_vertex_shader, source_light_fragment_shader);

		buffer_layout points_colors_layout_
		{
			ShaderDataType::Float3,
			ShaderDataType::Float3,
			ShaderDataType::Float2
		};

		points_colors_vbo_ = std::make_unique<vertex_buffer>(square_points, sizeof(square_points),
															 points_colors_layout_, vertex_buffer::Usage::Static);

		index_buffer_ = std::make_unique<index_buffer>(indexes, sizeof(indexes) / sizeof(GLuint), vertex_buffer::Usage::Static);

		VAO_1buffer_ = std::make_unique<vertex_array>();

		VAO_1buffer_->addVertexBuffer(*points_colors_vbo_);
		VAO_1buffer_->setIndexBuffer(*index_buffer_);


		m_window_ptr->setBackgroundColor(0.3f, 0.3f, 0.3f, 1.f);
		const auto& window_bg_color = m_window_ptr->getBackgroundColor();
		bg_color[0] = window_bg_color[0];
		bg_color[1] = window_bg_color[1];
		bg_color[2] = window_bg_color[2];
		bg_color[3] = window_bg_color[3];


		unsigned int width = 500;
		unsigned int height = 500;

		auto* data = new unsigned char[width * height * 3];
		generateSmileTexture(data, width, height);

		textureSmile = std::make_unique<texture2D>();
		textureQuads = std::make_unique<texture2D>();
		textureMandelbrotSet = std::make_unique<texture2D>();

		TextureParamsStorage tex_params_storage_;
		tex_params_storage_.texture_wrap_s = Wrap::Repeat;
		tex_params_storage_.texture_wrap_t = Wrap::Repeat;
		tex_params_storage_.texture_min_filter = Filter::LinearMipMapLinear;
		tex_params_storage_.texture_mag_filter = Filter::Linear;

		textureSmile->setData(data, width, height);
		textureSmile->setParametrs(tex_params_storage_);
		textureSmile->bind(0);
		
		//generateMandelbrotSet(data, width);
		//textureMandelbrotSet->setData(data, width, height);
		//textureMandelbrotSet->setParametrs(tex_params_storage_);
		//textureMandelbrotSet->bind(0);

		generateQuadsTexture(data, width, height);
		textureQuads->setData(data, width, height);
		textureQuads->setParametrs(tex_params_storage_);
		textureQuads->bind(1);

		delete[] data;


		engine::ecs::ECS::initialize();

		engine::ecs::entities::entity_id ID = engine::ecs::ECS::getEntitiesManager()->createEntity<engine::models::cube>();
		engine::ecs::ECS::getComponentsManager()->addComponent<engine::ecs::components::transform_component>(ID);
		engine::ecs::ECS::getSystemsManager()->addSystem<engine::ecs::systems::render_system>();

		LOG_INFO("'{0}' application started, size: {1}x{2}", m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
	}



	void editor_app::setEventListeners() noexcept
	{
		m_window_ptr->addEventListener<Events::Resize>(
			[this](const ResizeEventData& _size) -> void
			{
				renderer::setViewport(_size.width, _size.height);
				m_camera->setViewPortSize(_size.width, _size.height);
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

		float velosity = 0.003f;

		glm::vec3 movement_delta = { 0.f, 0.f, 0.f };
		glm::vec3 rotation_delta = { 0.f, 0.f, 0.f };

		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_LEFT_SHIFT))
		{
			velosity *= 5.f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_LEFT_CONTROL))
		{
			velosity /= 5.f;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_W))
		{
			movement_delta.x += velosity;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_S))
		{
			movement_delta.x -= velosity;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_D))
		{
			movement_delta.y += velosity;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_A))
		{
			movement_delta.y -= velosity;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_E))
		{
			movement_delta.z += velosity;
		}
		if (engine::input::keyboard::isKeyPressed(engine::input::Key::KEY_Q))
		{
			movement_delta.z -= velosity;
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

		auto io = ImGui::GetIO();
		if (!io.WantCaptureMouse)
		{
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
		}

		last_mouse_pos[0] = current_mouse_pos.x;
		last_mouse_pos[1] = current_mouse_pos.y;

		m_camera->moveAndRotate(movement_delta, rotation_delta);


		engine::ecs::ECS::update(1.f);
		

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



		renderer::setClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
		renderer::clear({ renderer::Mask::ColorBuffer, renderer::Mask::DepthBuffer });

		
		shader_program_->bind();

		static int currnet_frame = 0;
		shader_program_->setInt("current_frame", currnet_frame);
		m_camera->setProjectionMode(is_perspective_projection ? camera::Projection::Perspective : camera::Projection::Orthographic);
		shader_program_->setFloat("ambient_factor", ambient_factor);
		shader_program_->setFloat("diffuse_factor", diffuse_factor);
		shader_program_->setFloat("specular_factor", specular_factor);
		shader_program_->setFloat("shiniess", shiniess);
		shader_program_->setVector3f("source_light_color", glm::vec3(source_light_color[0], source_light_color[1], source_light_color[2]));
		shader_program_->setVector3f("source_light_position", glm::vec3(translate[0], translate[1], translate[2]));

		glm::mat4 model_matrix(1);
		for (const glm::vec3 position : positions)
		{
			glm::mat4 translate_matrix = glm::translate(model_matrix, position);
			shader_program_->setMatrix4f("model_view_matrix", m_camera->getViewMatrix() * translate_matrix);
			shader_program_->setMatrix4f("mvp_matrix", m_camera->getViewProjectionMatrix() * translate_matrix);
			shader_program_->setMatrix3f("normal_matrix", glm::mat3(glm::transpose(glm::inverse(translate_matrix))));
			renderer::draw(*VAO_1buffer_);
		}

		glm::mat4 model_matrix_2(1);
		model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(translate[0], translate[1], translate[2]));
		model_matrix_2 = glm::scale(model_matrix_2, glm::vec3(scale[0], scale[1], scale[2]));
		source_light_shader_program_->bind();
		source_light_shader_program_->setMatrix4f("mvp_matrix", m_camera->getViewProjectionMatrix() * model_matrix_2);
		source_light_shader_program_->setVector3f("source_light_color", glm::vec3(source_light_color[0], source_light_color[1], source_light_color[2]));
		renderer::draw(*VAO_1buffer_);

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
		ImGui::Separator();
		ImGui::Checkbox("Perspective projection", &is_perspective_projection);
		ImGui::Separator();
		if (ImGui::SliderFloat("Field of view", &field_of_view, 0.f, 180.f))
		{
			m_camera->setFieldOfView(field_of_view);
		}
		if (ImGui::SliderFloat("Near plane", &near_plane, 0.1f, 2.f))
		{
			m_camera->setNearPlane(near_plane);
		}
		if (ImGui::SliderFloat("Far plane", &far_plane, 2.f, 100.f))
		{
			m_camera->setFarPlane(far_plane);
		}
		ImGui::Separator();
		ImGui::ColorEdit4("Source light color", source_light_color);
		ImGui::SliderFloat("Ambient factor", &ambient_factor, 0.f, 1.f);
		ImGui::SliderFloat("Diffuse factor", &diffuse_factor, 0.f, 2.f);
		ImGui::SliderFloat("Specular factor", &specular_factor, 0.1f, 5.f);
		ImGui::SliderFloat("Shiniess", &shiniess, 0.1f, 100.f);
		ImGui::Separator();
		ImGui::SliderFloat3("Source light position", translate, -10.f, 10.f);
		ImGui::SliderFloat3("Source light scale", scale, 0.f, 10.f);
		ImGui::Separator();
		ImGui::End();

		UIModule::onUIDrawEnd_GlfwWindow_OpenGLRenderer();
	}



	editor_app::~editor_app()
	{
		engine::ecs::ECS::terminate();
		UIModule::onGLfwWindowShutdown_OpenGLRenderer();
		LOG_INFO("'{0}' application closed, size: {1}x{2}", m_window_ptr->getTitle(), m_window_ptr->getWidth(), m_window_ptr->getHeight());
	}
}
*/