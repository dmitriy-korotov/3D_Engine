#pragma once

#include <engine/render/open_gl/gl_types.hpp>
#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/binded_object.hpp>

#include <glm/fwd.hpp>	// glm dependens (TODO: try to remove)

#include <iostream>
#include <optional>



namespace engine::render::open_gl
{
	enum class ShaderType : uint8_t
	{
		vertex_shader,
		fragment_shader
	};

	class shader_program final: private util::nocopyeble, public interfaces::binded_object
	{
	public:

		shader_program(const std::string_view& _vertex_shader_source,
					   const std::string_view& _fragment_shader_source) noexcept;
		shader_program(shader_program&& _other) noexcept;
		shader_program& operator=(shader_program&& _right) noexcept;
		~shader_program();

		bool isCompiled() const noexcept;
		void setMatrix4f(const std::string_view& _varieble_name, const glm::mat4& _matrix) const noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;

	private:

		static std::optional<GLuint> createShader(ShaderType _shader_type, const std::string_view& _source) noexcept;

	private:

		bool m_is_compiled = false;
		GLuint m_id = 0;

	};
}