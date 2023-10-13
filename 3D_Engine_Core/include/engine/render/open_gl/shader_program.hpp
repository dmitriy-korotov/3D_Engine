#pragma once

#include <engine/render/open_gl/open_gl.hpp>

#include <engine/render/basic_shader_program.hpp>

#include <iostream>
#include <optional>



namespace engine::render::open_gl
{
	class shader_program final: public basic_shader_program
	{
	public:

		shader_program(const std::string_view& _vertex_shader_source,
					   const std::string_view& _fragment_shader_source) noexcept;
		shader_program(shader_program&& _other) noexcept;
		shader_program& operator=(shader_program&& _right) noexcept;
		~shader_program() override;

		void setMatrix4f(const std::string_view& _varieble_name, const glm::mat4& _matrix) const noexcept override;
		void setMatrix3f(const std::string_view& _varieble_name, const glm::mat3& _matrix) const noexcept override;
		void setVector3f(const std::string_view& _varieble_name, const glm::vec3& _vector) const noexcept override;
		void setVector4f(const std::string_view& _varieble_name, const glm::vec4& _vector) const noexcept override;
		void setInt(const std::string_view& _varieble_name, int _value) const noexcept override;
		void setFloat(const std::string_view& _varieble_name, float _value) const noexcept override;

		void bind() const noexcept override;
		void unbind() const noexcept override;

	private:

		static std::optional<GLuint> createShader(ShaderType _shader_type, const std::string_view& _source) noexcept;
		bool isProgramLinked() const noexcept;

	private:

		GLuint m_id = 0;

	};
}