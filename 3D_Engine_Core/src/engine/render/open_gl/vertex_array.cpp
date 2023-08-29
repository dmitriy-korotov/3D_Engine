#include <engine/render/open_gl/vertex_array.hpp>

#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/index_buffer.hpp>

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



	void vertex_array::addVertexBuffer(const vertex_buffer& _vertex_buffer) noexcept
	{
		bind();
		_vertex_buffer.bind();

		for (const auto& element : _vertex_buffer.getBufferLayout().getElements())
		{
			glEnableVertexAttribArray(m_amount_buffers_);
			glVertexAttribPointer(m_amount_buffers_,
								  element.components_count,
								  element.components_type,
								  GL_FALSE,
								  _vertex_buffer.getBufferLayout().getStride(),
								  reinterpret_cast<const void*>(element.offset));
			++m_amount_buffers_;
		}
	}



	void vertex_array::setIndexBuffer(const index_buffer& _index_buffer) noexcept
	{
		bind();
		_index_buffer.bind();
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