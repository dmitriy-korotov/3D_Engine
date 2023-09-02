#pragma once

#include <engine/render/open_gl/basic_open_gl_buffer.hpp>
#include <engine/render/open_gl/buffer_layout.hpp>



namespace engine::render::open_gl
{
	class vertex_buffer final: public basic_open_gl_buffer
	{
	public:

		vertex_buffer(const void* _data, size_t _size, buffer_layout _buffer_layout, Usage _usage_type) noexcept;
		vertex_buffer(vertex_buffer&& _other) noexcept;
		vertex_buffer& operator=(vertex_buffer&& _right) noexcept;
		~vertex_buffer() override;

		void bind() const noexcept override;
		void unbind() const noexcept override;

		const buffer_layout& getBufferLayout() const noexcept;

	private:

		buffer_layout m_buffer_layout_;

	};
}