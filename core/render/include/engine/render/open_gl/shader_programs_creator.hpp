#pragma once

#include <engine/render/basic_shader_programs_creator.hpp>



namespace engine::render::open_gl
{
	class shader_programs_creator: public basic_shader_programs_creator
	{
	public:

		[[nodiscard]] shader_ptrogram_ptr_t createShaderProgram(std::string_view _vertex_shader,
																std::string_view _fragment_shader) const noexcept override;

	};
}