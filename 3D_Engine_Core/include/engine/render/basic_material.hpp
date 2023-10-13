#pragma once

#include <engine/interfaces/usage_object.hpp>

#include <engine/util/nocopyeble.hpp>



namespace engine::render
{
	class basic_material: public interfaces::usage_object, private util::nocopyeble
	{
	public:

		basic_material() = default;
		virtual ~basic_material() = default;

	};
}