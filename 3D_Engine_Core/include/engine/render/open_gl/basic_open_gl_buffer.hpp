#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/binded_object.hpp>

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

	protected:

		static auto usageToGLenum(Usage _usage_type) noexcept;

	protected:

		unsigned int m_id = 0;

	};
}