#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <array>



namespace engine::ecs::systems
{
	class UI_scene: public basic_system
	{
	public:

		void update(float _delta_time) const noexcept;

	private:

		mutable std::array<float, 4> m_bacgroud_color = { 0.f, 0.f, 0.f, 1.f };
		mutable std::array<float, 3> m_light_direction = { 0.f, 0.f, 0.f };

	};
}