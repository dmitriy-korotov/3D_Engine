#pragma once

#include <iostream>
#include <optional>



namespace engine::render
{
	enum class shader_type : uint8_t
	{
		vertex_shader,
		fragment_shader
	};



	class shader_program
	{
	public:

		shader_program(const shader_program&) = delete;
		shader_program& operator=(const shader_program&) = delete;



		shader_program(const std::string_view& _vertex_shader_source,
					   const std::string_view& _fragment_shader_source) noexcept;
		shader_program(shader_program&& _other) noexcept;
		shader_program& operator=(shader_program&& _right) noexcept;

		bool isCompiled() const noexcept;

		void bind() const noexcept;
		void unbind() const noexcept;

	private:

		static std::optional<unsigned int> createShader(shader_type _shader_type, const std::string_view& _source) noexcept;

	private:

		bool m_is_compiled = false;
		unsigned int m_id = 0;

	};
}