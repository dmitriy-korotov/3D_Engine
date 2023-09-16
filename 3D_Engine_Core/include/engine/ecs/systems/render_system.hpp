#pragma once

#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	class render_system final : public basic_system
	{
	public:

		void update(float _delta_time) noexcept override;

	};
}