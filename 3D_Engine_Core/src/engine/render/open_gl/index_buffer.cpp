#include <engine/render/open_gl/index_buffer.hpp>

#include <glad/glad.h>



namespace engine::render
{
	index_buffer::index_buffer(const void* _data, size_t _count, vertex_buffer::Usage _usage_type)
	{
		glGenBuffers(1, &m_id_);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _count, _data, GL_STATIC_DRAW);
	}



	void index_buffer::bind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_);
	}



	void index_buffer::unbind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}