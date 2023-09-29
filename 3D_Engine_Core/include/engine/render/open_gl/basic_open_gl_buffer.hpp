#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/binded_object.hpp>
#include <engine/render/open_gl/gl_types.hpp>

#include <stdint.h>



namespace engine::render::open_gl
{
	class basic_open_gl_buffer: private util::nocopyeble, public interfaces::binded_object
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

		bool isDataSet() const noexcept;
		
	protected:

		GLenum usageToGLenum(Usage _usage_type) noexcept;

	protected:

		GLuint m_id = 0;
		bool m_is_data_set = false;

	};
}