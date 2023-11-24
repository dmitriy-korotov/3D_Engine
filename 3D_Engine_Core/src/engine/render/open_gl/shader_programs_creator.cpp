#include <engine/render/open_gl/shader_programs_creator.hpp>

#include <engine/render/open_gl/shader_program.hpp>



namespace engine::render::open_gl
{
	auto shader_programs_creator::createShaderProgram(std::string_view _vertex_shader,
													  std::string_view _fragment_shader) const noexcept -> shader_ptrogram_ptr_t
	{
		return std::make_shared<shader_program>(_vertex_shader, _fragment_shader);
	}
}