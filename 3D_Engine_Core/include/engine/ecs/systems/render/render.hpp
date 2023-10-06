#pragma once

#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	class render final: public basic_system
	{
	public:

		void update(float _delta_time) const noexcept override;

	};
}