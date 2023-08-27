#pragma once

#include <engine/render/open_gl/vertex_buffer.hpp>



namespace engine::render
{
	class index_buffer
	{
	public:

		index_buffer(const void* _data, size_t _count, vertex_buffer::Usage _usage_type);

		void bind() const noexcept;
		void unbind() const noexcept;

	private:

		unsigned int m_id_ = 0;
		unsigned int m_indexes_count_ = 0;

	};
}