#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/binded_object.hpp>
#include <engine/render/open_gl/gl_types.hpp>

#include <stdint.h>



namespace engine::render
{
	class basic_open_gl_buffer : protected util::nocopyeble, protected binded_object
	{
	public:

		enum class Usage : uint8_t
		{
			Static,
			Dynamic,
			Stream
		};

		basic_open_gl_buffer() = default;
		basic_open_gl_buffer(GLuint _buffer_id) noexcept;

	protected:

		GLenum usageToGLenum(Usage _usage_type) noexcept;

	protected:

		GLuint m_id = 0;

	};
}