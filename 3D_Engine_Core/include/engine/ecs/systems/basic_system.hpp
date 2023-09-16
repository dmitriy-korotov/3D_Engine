#pragma once

#include <engine/util/nocopyeble.hpp>



namespace engine::ecs::systems
{
	class basic_system : private util::nocopyeble
	{
	public:

		basic_system() = default;
		virtual ~basic_system() {}

		virtual void update(float _delta_time) = 0;

	};
}