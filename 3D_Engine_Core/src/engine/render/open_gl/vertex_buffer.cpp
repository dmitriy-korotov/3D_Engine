#include <engine/render/open_gl/vertex_buffer.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>



namespace engine::render
{
	constexpr GLenum usageToGLenum(vertex_buffer::Usage _usage_type) noexcept
	{
		switch (_usage_type)
		{
		case engine::render::vertex_buffer::Usage::Static:
			return GL_STATIC_DRAW;
		case engine::render::vertex_buffer::Usage::Dynamic:
			return GL_DYNAMIC_DRAW;
		case engine::render::vertex_buffer::Usage::Stream:
			return GL_STREAM_DRAW;
		}
		LOG_ERROR("ERROR: Can't find this usage.");

		return GL_STREAM_DRAW;
	}





	vertex_buffer::vertex_buffer(const void* _data, size_t _size, Usage _usage_type) noexcept
	{
		glGenBuffers(1, &m_id);
		bind();
		glBufferData(GL_ARRAY_BUFFER, _size, _data, usageToGLenum(_usage_type));
	}



	vertex_buffer::vertex_buffer(vertex_buffer&& _other) noexcept
			: m_id(_other.m_id)
	{
		_other.m_id = 0;
	}



	vertex_buffer& vertex_buffer::operator=(vertex_buffer&& _right) noexcept
	{
		m_id = _right.m_id;
		_right.m_id = 0;

		return *this;
	}



	vertex_buffer::~vertex_buffer()
	{
		glDeleteBuffers(1, &m_id);
	}



	void vertex_buffer::bind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}



	void vertex_buffer::unbind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}