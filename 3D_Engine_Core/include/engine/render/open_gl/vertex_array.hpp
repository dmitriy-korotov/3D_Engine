#pragma once

#include <engine/interfaces/binded_object.hpp>
#include <engine/render/open_gl/gl_types.hpp>
#include <engine/util/nocopyeble.hpp>

#include <stdint.h>



namespace engine::render
{
	class vertex_buffer;
	class index_buffer;



	class vertex_array final: private util::nocopyeble, private binded_object
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

	private:

		GLuint m_id = 0;
		uint16_t m_amount_buffers = 0;

	};
}