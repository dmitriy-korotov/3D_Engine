#pragma once

#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	class move_camera_system : public basic_system
	{
	public:

		void update(float _delta_time) const noexcept override;

	};
}