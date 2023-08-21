#pragma once

#include <iostream>



namespace engine::render
{
	class vertex_buffer
	{
	public:

		enum class Usage : uint8_t
		{
			Static,
			Dynamic,
			Stream
		};



		vertex_buffer(const vertex_buffer&) = delete;
		vertex_buffer& operator=(const vertex_buffer&) = delete;



		vertex_buffer(const void* _data, size_t _size, Usage _usage_type) noexcept;
		vertex_buffer(vertex_buffer&& _other) noexcept;
		vertex_buffer& operator=(vertex_buffer&& _right) noexcept;
		~vertex_buffer();

		void bind() const noexcept;
		void unbind() const noexcept;

	private:

		unsigned int m_id = 0;

	};
}