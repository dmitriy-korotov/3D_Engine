#include <engine/render/open_gl/index_buffer.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	index_buffer::index_buffer() noexcept
	{
		glGenBuffers(1, &m_id);
	}



	index_buffer::index_buffer(const void* _data, uint64_t _indexes_count, Usage _usage_type)
			: m_indexes_count(_indexes_count)
	{
		glGenBuffers(1, &m_id);
		setIndexes(_data, _indexes_count, _usage_type);
	}



	index_buffer::index_buffer(index_buffer&& _other) noexcept
			: basic_open_gl_buffer(_other.m_id)
			, m_indexes_count(_other.m_indexes_count)
	{
		_other.m_id = 0;
		_other.m_indexes_count = 0;
	}



	index_buffer& index_buffer::operator=(index_buffer&& _right) noexcept
	{
		if (m_id != _right.m_id)
		{
			glDeleteBuffers(1, &m_id);

			m_id = _right.m_id;
			m_indexes_count = _right.m_indexes_count;

			_right.m_id = 0;
			_right.m_indexes_count = 0;
		}
		return *this;
	}



	index_buffer::~index_buffer()
	{
		glDeleteBuffers(1, &m_id);
	}



	void index_buffer::setIndexes(const void* _data, uint64_t _indexes_count, Usage _usage_type) noexcept
	{
		if (!m_is_data_set)
		{
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indexes_count, _data, usageToGLenum(_usage_type));
			m_is_data_set = true;
		}
		else
		{
			LOG_WARN("[Index buffeer WARN] Data already setted.");
		}
	}



	void index_buffer::bind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}



	void index_buffer::unbind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}



	uint64_t index_buffer::getIndexesCount() const noexcept
	{
		return m_indexes_count;
	}
}