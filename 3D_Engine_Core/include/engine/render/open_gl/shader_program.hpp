#pragma once

#include <engine/render/open_gl/gl_types.hpp>
#include <engine/util/nocopyeble.hpp>

#include <iostream>
#include <optional>



namespace engine::render
{
	enum class ShaderType : uint8_t
	{
		vertex_shader,
		fragment_shader
	};



	class shader_program : private util::nocopyeble
	{
	public:

		shader_program(const std::string_view& _vertex_shader_source,
					   const std::string_view& _fragment_shader_source) noexcept;
		shader_program(shader_program&& _other) noexcept;
		shader_program& operator=(shader_program&& _right) noexcept;
		~shader_program();

		bool isCompiled() const noexcept;

		void bind() const noexcept;
		void unbind() const noexcept;

	private:

		static std::optional<unsigned int> createShader(ShaderType _shader_type, const std::string_view& _source) noexcept;

	private:

		bool m_is_compiled = false;
		GLuint m_id = 0;

	};
}