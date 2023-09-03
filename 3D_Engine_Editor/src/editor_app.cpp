#include <editor_app.hpp>



/*
* //-----------------------------------------------------------------------------------------------------------------//   
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
using namespace engine::render::open_gl;



std::unique_ptr<shader_program> shader_program_;

std::unique_ptr<vertex_buffer> points_colors_vbo_;
std::unique_ptr<index_buffer> index_buffer_;

std::unique_ptr<vertex_array> VAO_1buffer_;
//-----------------------------------------------------------------------------------------------------------------//
*/



editor_app::editor_app(uint16_t _width, uint16_t _height,
				       const std::string_view& _editor_name)
		: application(_width, _height, _editor_name)
{ }



void editor_app::onUpdate() noexcept
{ }



/*
//-----------------------------------------------------------------------------------------------------------------//   
m_window_ptr->addEventListener<Events::Resize>(
    [this](const ResizeEventData& _size) -> void
    {
        LOG_INFO("[RESIZE EVENT] Window '{0}', size: {1}x{2}", m_window_ptr->getTitle(), _size.width, _size.height);
        render::open_gl::renderer::setViewport(_size.width, _size.height);
    });

m_window_ptr->addEventListener<Events::Close>(
    [this]() -> void
    {
        LOG_INFO("[CLOSE EVENT] Window '{0}' closed", m_window_ptr->getTitle());
        m_is_closed = true;
    });
//-----------------------------------------------------------------------------------------------------------------//
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

camera = std::make_unique<render::camera>();

//-----------------------------------------------------------------------------------------------------------------//

renderer::setClearColor(m_bg_color_[0], m_bg_color_[1], m_bg_color_[2], m_bg_color_[3]);
renderer::clear(renderer::Mask::ColorBuffer);

shader_program_->bind();

static bool is_one_buffer = true;
if (is_one_buffer)
{
	VAO_1buffer_->bind();
	renderer::draw(*VAO_1buffer_);
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

shader_program_->setMatrix4f("model_matrix", model_matrix);

camera->setPositionAndRotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
								glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
camera->setProjectionMode(is_perspective_projection ? render::camera::Projection::Perspective : render::camera::Projection::Orthographic);

shader_program_->setMatrix4f("view_projection_matrix", camera->getViewProjectionMatrix());


ui::ImGuiModule::onUIDrawBegin();

bool open = true;
ui::ImGuiModule::ShowExampleAppDockSpace(&open);
ImGui::ShowDemoWindow();

ImGui::Begin("BG Color Editor");
ImGui::ColorEdit4("Background color", m_bg_color_.data());
ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
ImGui::SliderFloat3("Camera rotation", camera_rotation, -360.f, 360.f);
ImGui::Checkbox("Perspective projection", &is_perspective_projection);
ImGui::End();

ui::ImGuiModule::onUIDrawEnd();

window::onUpdate();
*/