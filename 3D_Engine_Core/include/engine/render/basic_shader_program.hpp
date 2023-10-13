#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/binded_object.hpp>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

#include <string>



namespace engine::render
{
	enum class ShaderType : uint8_t
	{
		vertex_shader,
		fragment_shader
	};

	class basic_shader_program: private util::nocopyeble, public interfaces::binded_object
	{
	public:

		basic_shader_program() = default;
		basic_shader_program(basic_shader_program&& _other) noexcept;
		basic_shader_program& operator=(basic_shader_program&& _right) noexcept;

		bool isCompiled() const noexcept;

		virtual void setMatrix4f(const std::string_view& _varieble_name, const glm::mat4& _matrix) const noexcept = 0;
		virtual void setMatrix3f(const std::string_view& _varieble_name, const glm::mat3& _matrix) const noexcept = 0;
		virtual void setVector3f(const std::string_view& _varieble_name, const glm::vec3& _vector) const noexcept = 0;
		virtual void setVector4f(const std::string_view& _varieble_name, const glm::vec4& _vector) const noexcept = 0;
		virtual void setInt(const std::string_view& _varieble_name, int _value) const noexcept = 0;
		virtual void setFloat(const std::string_view& _varieble_name, float _value) const noexcept = 0;

	protected:

		bool m_is_compiled = false;

	};
}