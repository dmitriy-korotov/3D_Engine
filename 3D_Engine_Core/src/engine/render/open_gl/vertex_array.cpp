#include <engine/render/open_gl/vertex_array.hpp>

#include <engine/render/open_gl/vertex_buffer.hpp>

#include <glad/glad.h>



namespace engine::render
{
	vertex_array::vertex_array() noexcept
	{
		glGenVertexArrays(1, &m_id_);
	}



	vertex_array::~vertex_array()
	{
		glDeleteBuffers(1, &m_id_);
	}



	void vertex_array::addBuffer(const vertex_buffer& _buffer) noexcept
	{
		bind();

		glEnableVertexAttribArray(m_amount_buffers_);
		_buffer.bind();
		glVertexAttribPointer(m_amount_buffers_, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		++m_amount_buffers_;
	}



	void vertex_array::bind() const noexcept
	{
		glBindVertexArray(m_id_);
	}



	void vertex_array::unbind() const noexcept
	{
		glBindVertexArray(0);
	}
}