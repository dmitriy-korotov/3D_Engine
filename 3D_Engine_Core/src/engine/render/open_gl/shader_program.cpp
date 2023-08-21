#include <engine/render/open_gl/shader_program.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine::render
{
	shader_program::shader_program(const std::string_view& _vertex_shader_source,
		const std::string_view& _fragment_shader_source) noexcept
	{
		auto vertex_shader_ = shader_program::createShader(shader_type::vertex_shader, _vertex_shader_source);
		if (!vertex_shader_.has_value())
		{
			LOG_CRITICAL("ERROR: vertex shader not created.");
			return;
		}

		auto fragment_shader_ = shader_program::createShader(shader_type::fragment_shader, _fragment_shader_source);
		if (!fragment_shader_.has_value())
		{
			LOG_CRITICAL("ERROR: fragment shader not created.");
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
		glDeleteProgram(m_id);

		m_id = _right.m_id;
		m_is_compiled = _right.m_is_compiled;

		_right.m_id = 0;
		_right.m_is_compiled = false;

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



	std::optional<unsigned int> shader_program::createShader(shader_type _shader_type, const std::string_view& _source) noexcept
	{
		GLuint shader_ = 0;
		switch (_shader_type)
		{
		case engine::render::shader_type::vertex_shader:
			shader_ = glCreateShader(GL_VERTEX_SHADER);
			break;
		case engine::render::shader_type::fragment_shader:
			shader_ = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}

		const char* source_code_ = _source.data();
		glShaderSource(shader_, 1, &source_code_, nullptr);
		glCompileShader(shader_);

		GLint success_;
		glGetShaderiv(shader_, GL_COMPILE_STATUS, &success_);
		if (success_ == GL_FALSE)
		{
			char info_log_[1024] = {};
			glGetShaderInfoLog(shader_, 1024, nullptr, info_log_);
			LOG_CRITICAL("ERROR: Can't compiling shader: {}", info_log_);
			
			glDeleteShader(shader_);
			
			return std::nullopt;
		}
		return shader_;
	}
}