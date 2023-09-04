#include <engine/render/open_gl/shader_program.hpp>

#include <engine/logging/log.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
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

		m_is_compiled = true;
	}



	shader_program::shader_program(shader_program&& _other) noexcept
			: m_id(_other.m_id)
			, m_is_compiled(_other.m_is_compiled)
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



	bool shader_program::isCompiled() const noexcept
	{
		return m_is_compiled;
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

		const char* source_code = _source.data();
		glShaderSource(shader, 1, &source_code, nullptr);
		glCompileShader(shader);

		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			char info_log[1024] = {};
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			LOG_CRITICAL("[[Shader Program ERROR]] Can't compiling shader: {0}", info_log);
			
			glDeleteShader(shader);
			
			return std::nullopt;
		}
		return shader;
	}



	void shader_program::setMatrix4f(const std::string_view& _varieble_name, const glm::mat4& _matrix) const noexcept
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, _varieble_name.data()), 1, GL_FALSE, glm::value_ptr(_matrix));
	}
}