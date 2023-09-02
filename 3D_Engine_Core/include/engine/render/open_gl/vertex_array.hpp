#pragma once

#include <engine/interfaces/binded_object.hpp>
#include <engine/render/open_gl/gl_types.hpp>
#include <engine/util/nocopyeble.hpp>

#include <stdint.h>



namespace engine::render::open_gl
{
	class vertex_buffer;
	class index_buffer;

	class vertex_array final: private util::nocopyeble, public interfaces::binded_object
	{
	public:

		explicit vertex_array() noexcept;
		vertex_array(vertex_array&& _other) noexcept;
		vertex_array& operator=(vertex_array&& _right) noexcept;
		~vertex_array();

		void addVertexBuffer(const vertex_buffer& _vertex_buffer) noexcept;
		void setIndexBuffer(const index_buffer& _index_buffer) noexcept;
		void bind() const noexcept override;
		void unbind() const noexcept override;

		uint64_t getIndexesCount() const noexcept;

	private:

		GLuint m_id = 0;
		uint16_t m_amount_buffers = 0;
		uint64_t m_indexes_count = 0;

	};
}