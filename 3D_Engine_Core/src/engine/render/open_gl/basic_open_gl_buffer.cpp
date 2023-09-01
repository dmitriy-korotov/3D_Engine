#include <engine/render/open_gl/basic_open_gl_buffer.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>



namespace engine::render
{
	GLenum basic_open_gl_buffer::usageToGLenum(Usage _usage_type) noexcept
	{
		switch (_usage_type)
		{
		case Usage::Static:			return GL_STATIC_DRAW;
		case Usage::Dynamic:		return GL_DYNAMIC_DRAW;
		case Usage::Stream:			return GL_STREAM_DRAW;
		}
		LOG_ERROR("ERROR: Can't find this usage (code: {0}).", static_cast<uint8_t>(_usage_type));

		return GL_STREAM_DRAW;
	}



	basic_open_gl_buffer::basic_open_gl_buffer(GLuint _buffer_id) noexcept
			: m_id(_buffer_id)
	{ }
}