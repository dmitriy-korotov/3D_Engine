#include <engine/render/open_gl/shader_programs_creator.hpp>

#include <engine/render/open_gl/shader_program.hpp>



namespace engine::render::open_gl
{
	shader_programs_creator::shader_ptrogram_ptr_t shader_programs_creator::createShaderProgram(std::string_view _vertex_shader,
																								std::string_view _fragment_shader) const noexcept
	{
		return std::make_shared<shader_program>(_vertex_shader, _fragment_shader);
	}
}