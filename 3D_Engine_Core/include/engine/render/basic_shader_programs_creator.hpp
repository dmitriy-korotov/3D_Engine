#pragma once

#include <engine/render/fwd/basic_shader_program.hpp>

#include <string>
#include <memory>



namespace engine::render
{
	class basic_shader_programs_creator
	{
	public:

		using shader_ptrogram_ptr_t = std::shared_ptr<basic_shader_program>;

		[[nodiscard]] virtual shader_ptrogram_ptr_t createShaderProgram(std::string_view _vertex_shader,
																		std::string_view _fragment_shader) const noexcept = 0;

	};
}