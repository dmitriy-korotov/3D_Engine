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
		_buffer.bind();

		for (const auto& element : _buffer.getBufferLayout().getElements())
		{
			glEnableVertexAttribArray(m_amount_buffers_);
			glVertexAttribPointer(m_amount_buffers_,
								  element.components_count_,
								  element.components_type_,
								  GL_FALSE,
								  _buffer.getBufferLayout().getStride(),
								  reinterpret_cast<const void*>(element.offset_));
			++m_amount_buffers_;
		}
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