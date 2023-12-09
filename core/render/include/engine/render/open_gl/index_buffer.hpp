#pragma once

#include <engine/render/open_gl/basic_open_gl_buffer.hpp>



namespace engine::render::open_gl
{
	class index_buffer final: public basic_open_gl_buffer
	{
	public:

		index_buffer() noexcept;
		index_buffer(const void* _data, uint64_t _indexes_count, Usage _usage_type);
		index_buffer(index_buffer&& _other) noexcept;
		index_buffer& operator=(index_buffer&& _right) noexcept;
		~index_buffer() override;

		void setIndexes(const void* _data, uint64_t _indexes_count, Usage _usage_type) noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;

		uint64_t getIndexesCount() const noexcept;

	private:

		uint64_t m_indexes_count = 0;

	};
}