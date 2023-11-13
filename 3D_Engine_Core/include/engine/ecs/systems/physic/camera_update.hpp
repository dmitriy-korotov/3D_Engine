#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <engine/ecs/components/physic/fwd/movement_velocity.hpp>
#include <engine/ecs/components/physic/fwd/rotate_velocity.hpp>
#include <engine/ecs/components/physic/fwd/movement.hpp>
#include <engine/ecs/components/physic/fwd/rotate.hpp>

#include <glm/vec2.hpp>



namespace engine::ecs::systems
{
	using namespace components;

	class camera_update: public basic_system
	{
	public:

		static constexpr std::string_view system_name = "camera_update";

		void update(float _delta_time) const noexcept override;

	private:

		void moveCamera(const movement& _movement_component, 
						const movement_velocity& _movement_velocity_component, float _delta_time) const noexcept;
		void rotateCamera(const rotate& _rotate_component,
						  const rotate_velocity& _rotate_velocity_component, float _delta_time) const noexcept;

		serialized_view_t serialize() const override;

	private:

		mutable glm::dvec2 m_last_cursor_position = glm::dvec2(0, 0);

	};
}