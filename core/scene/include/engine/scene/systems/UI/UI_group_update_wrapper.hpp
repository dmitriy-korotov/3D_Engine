#pragma once

#include <engine/ecs/systems/basic_group_update_wrapper.hpp>



namespace engine::scene
{
	class UI_group_update_wrapper : public ecs::systems::basic_group_update_wrapper
	{
	public:

		void preUpdate(float _delta_time) noexcept override;
		void postUpdate(float _delta_time) noexcept override;

	};
}