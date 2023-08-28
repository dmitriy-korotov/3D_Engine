#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/binded_object.hpp>



namespace engine::render
{
	class basic_open_gl_buffer : protected util::nocopyeble, protected binded_object
	{
	protected:

		unsigned int m_id = 0;

	};
}