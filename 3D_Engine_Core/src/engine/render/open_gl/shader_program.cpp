#include <engine/render/open_gl/shader_program.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/util/shader_preprocessor.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	static constexpr std::string_view toString(ShaderType _shader_type) noexcept
	{
		switch (_shader_type)
		{
		case ShaderType::vertex_shader:			return "vertex shader";
		case ShaderType::fragment_shader:		return "fragment shader";
		}
		return "vertex shader";
	}



	shader_program::shader_program(const std::string_view& _vertex_shader_source,
								   const std::string_view& _fragment_shader_source) noexcept
	{
		auto vertex_shader_ = shader_program::createShader(ShaderType::vertex_shader, _vertex_shader_source);
		if (!vertex_shader_.has_value())
		{
			LOG_CRITICAL("[Shader Program ERROR] Vertex shader is not created.");
			return;
		}

		auto fragment_shader_ = shader_program::createShader(ShaderType::fragment_shader, _fragment_shader_source);
		if (!fragment_shader_.has_value())
		{
			LOG_CRITICAL("[Shader Program ERROR]: Fragment shader is not created.");
			glDeleteShader(*vertex_shader_);
			return;
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertex_shader_.value());
		glAttachShader(m_id, fragment_shader_.value());
		glLinkProgram(m_id);

		glDetachShader(m_id, *vertex_shader_);
		glDetachShader(m_id, *fragment_shader_);
		glDeleteShader(*vertex_shader_);
		glDeleteShader(*fragment_shader_);
		
		if (isProgramLinked())
			m_is_compiled = true;
	}



	shader_program::shader_program(shader_program&& _other) noexcept
			: basic_shader_program(std::move(_other))
			, m_id(_other.m_id)
	{
		_other.m_id = 0;
		_other.m_is_compiled = false;
	}



	shader_program& shader_program::operator=(shader_program&& _right) noexcept
	{
		if (m_id != _right.m_id)
		{
			glDeleteProgram(m_id);

			m_id = _right.m_id;
			m_is_compiled = _right.m_is_compiled;

			_right.m_id = 0;
			_right.m_is_compiled = false;
		}
		return *this;
	}



	shader_program::~shader_program()
	{
		glDeleteProgram(m_id);
	}



	void shader_program::bind() const noexcept
	{
		glUseProgram(m_id);
	}



	void shader_program::unbind() const noexcept
	{
		glUseProgram(0);
	}



	std::optional<GLuint> shader_program::createShader(ShaderType _shader_type, const std::string_view& _source) noexcept
	{
		GLuint shader = 0;
		switch (_shader_type)
		{
		case ShaderType::vertex_shader:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::fragment_shader:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}

		utility::shader_preprocessor preprocessor(_source);
		if (!preprocessor.isSuccessfully())
		{
			LOG_ERROR("[Shader Program ERROR] Can't preprocesse '{0}' shader", toString(_shader_type));
			return std::nullopt;
		}

		const char* source_code = preprocessor.getResult().data();
		glShaderSource(shader, 1, &source_code, nullptr);
		glCompileShader(shader);

		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			char info_log[1024] = {};
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			LOG_CRITICAL("[Shader Program ERROR] Can't compiling shader: {0}", info_log);
			
			glDeleteShader(shader);
			
			return std::nullopt;
		}
		return shader;
	}



	bool shader_program::isProgramLinked() const noexcept
	{
		GLint success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			char info_log[1024] = {};
			glGetProgramInfoLog(m_id, 1024, nullptr, info_log);
			LOG_CRITICAL("[Shader Program ERROR] Can't link program: {0}", info_log);
			return false;
		}
		return true;
	}



	void shader_program::setMatrix4f(const std::string_view& _varieble_name, const glm::mat4& _matrix) const noexcept
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, _varieble_name.data()), 1, GL_FALSE, glm::value_ptr(_matrix));
	}



	void shader_program::setMatrix3f(const std::string_view& _varieble_name, const glm::mat3& _matrix) const noexcept
	{
		glUniformMatrix3fv(glGetUniformLocation(m_id, _varieble_name.data()), 1, GL_FALSE, glm::value_ptr(_matrix));
	}



	void shader_program::setVector3f(const std::string_view& _varieble_name, const glm::vec3& _vector) const noexcept
	{
		glUniform3f(glGetUniformLocation(m_id, _varieble_name.data()), _vector.x, _vector.y, _vector.z);
	}



	void shader_program::setVector4f(const std::string_view& _varieble_name, const glm::vec4& _vector) const noexcept
	{
		glUniform4f(glGetUniformLocation(m_id, _varieble_name.data()), _vector.x, _vector.y, _vector.z, _vector.w);
	}



	void shader_program::setInt(const std::string_view& _varieble_name, int _value) const noexcept
	{
		glUniform1i(glGetUniformLocation(m_id, _varieble_name.data()), _value);
	}



	void shader_program::setFloat(const std::string_view& _varieble_name, float _value) const noexcept
	{
		glUniform1f(glGetUniformLocation(m_id, _varieble_name.data()), _value);
	}
}