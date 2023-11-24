#include <engine/render/open_gl/vertex_buffer.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	vertex_buffer::vertex_buffer() noexcept
	{
		glGenBuffers(1, &m_id);
	}



	vertex_buffer::vertex_buffer(const void* _data, size_t _size, buffer_layout _buffer_layout, Usage _usage_type) noexcept
	{
		glGenBuffers(1, &m_id);
		setData(_data, _size, _buffer_layout, _usage_type);
	}



	vertex_buffer::vertex_buffer(vertex_buffer&& _other) noexcept
			: basic_open_gl_buffer(_other.m_id)
			, m_buffer_layout(std::move(_other.m_buffer_layout))
	{
		_other.m_id = 0;
	}



	auto vertex_buffer::operator=(vertex_buffer&& _right) noexcept -> vertex_buffer&
	{
		if (m_id != _right.m_id)
		{
			m_id = _right.m_id;
			m_buffer_layout = std::move(_right.m_buffer_layout);
			_right.m_id = 0;
		}
		return *this;
	}



	vertex_buffer::~vertex_buffer()
	{
		glDeleteBuffers(1, &m_id);
	}



	auto vertex_buffer::setData(const void* _data, size_t _size, const buffer_layout& _buffer_layout, Usage _usage_type) noexcept -> void
	{
		if (!m_is_data_set)
		{
			m_buffer_layout = _buffer_layout;
			bind();
			glBufferData(GL_ARRAY_BUFFER, _size, _data, usageToGLenum(_usage_type));
			m_is_data_set = true;
		}
	}



	auto vertex_buffer::bind() const noexcept -> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}



	auto vertex_buffer::unbind() const noexcept -> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	auto vertex_buffer::getBufferLayout() const noexcept -> const buffer_layout&
	{
		return m_buffer_layout;
	}
}