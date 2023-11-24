#include <engine/render/open_gl/vertex_array.hpp>

#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/index_buffer.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	vertex_array::vertex_array() noexcept
	{
		glGenVertexArrays(1, &m_id);
	}



	vertex_array::vertex_array(vertex_array&& _other) noexcept
			: m_id(_other.m_id)
			, m_amount_buffers(_other.m_amount_buffers)
			, m_indexes_count(_other.m_indexes_count)
	{
		_other.m_id = 0;
		_other.m_amount_buffers = 0;
		_other.m_indexes_count = 0;
	}



	auto vertex_array::operator=(vertex_array&& _right) noexcept -> vertex_array&
	{
		if (m_id != _right.m_id)
		{
			glDeleteVertexArrays(1, &m_id);

			m_id = _right.m_id;
			m_amount_buffers = _right.m_amount_buffers;
			m_indexes_count = _right.m_indexes_count;

			_right.m_id = 0;
			_right.m_amount_buffers = 0;
			_right.m_indexes_count = 0;
		}
		return *this;
	}



	vertex_array::~vertex_array()
	{
		glDeleteVertexArrays(1, &m_id);
	}



	auto vertex_array::addVertexBuffer(const vertex_buffer& _vertex_buffer) noexcept -> void
	{
		bind();
		_vertex_buffer.bind();

		for (const auto& element : _vertex_buffer.getBufferLayout().getElements())
		{
			glEnableVertexAttribArray(m_amount_buffers);
			glVertexAttribPointer(m_amount_buffers,
								  element.components_count,
								  element.components_type,
								  GL_FALSE,
								  _vertex_buffer.getBufferLayout().getStride(),
								  reinterpret_cast<const void*>(element.offset));
			++m_amount_buffers;
		}
	}



	auto vertex_array::setIndexBuffer(const index_buffer& _index_buffer) noexcept -> void
	{
		m_indexes_count = _index_buffer.getIndexesCount();
		bind();
		_index_buffer.bind();
	}



	auto vertex_array::getIndexesCount() const noexcept -> uint64_t
	{
		return m_indexes_count;
	}



	auto vertex_array::bind() const noexcept -> void
	{
		glBindVertexArray(m_id);
	}



	auto vertex_array::unbind() const noexcept -> void
	{
		glBindVertexArray(0);
	}
}