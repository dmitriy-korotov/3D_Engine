#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <engine/ecs/components/physic/fwd/velocity.hpp>
#include <engine/ecs/components/physic/fwd/movement.hpp>

#include <glm/vec2.hpp>



namespace engine::ecs::systems
{
	using components::movement;
	using components::velocity;

	class camera_update: public basic_system
	{
	public:

		void update(float _delta_time) const noexcept override;

	private:

		void translateCamera(movement& _transform_component, 
							 velocity& _move_component, float _delta_time) const noexcept;
		void rotateCamera(movement& _transform_component,
						  velocity& _move_component, float _delta_time) const noexcept;

	private:

		mutable glm::dvec2 m_last_cursor_position = glm::dvec2(0, 0);

	};
}