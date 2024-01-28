#pragma once

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/physic/fwd/movement_velocity.hpp>
#include <engine/scene/components/physic/fwd/rotate_velocity.hpp>
#include <engine/scene/components/physic/fwd/movement.hpp>
#include <engine/scene/components/physic/fwd/rotate.hpp>

#include <glm/vec2.hpp>



namespace engine::scene::systems
{
	using namespace components;

	class camera_update: public scene_system
	{
	public:

		static constexpr std::string_view system_name = "camera_update";

		void update(float _delta_time) noexcept override;

	private:

		void moveCamera(const movement& _movement_component, 
						const movement_velocity& _movement_velocity_component, float _delta_time) const noexcept;
		void rotateCamera(const rotate& _rotate_component,
						  const rotate_velocity& _rotate_velocity_component, float _delta_time) noexcept;

		serialized_view_t serialize() const override;

	private:

		glm::dvec2 m_last_cursor_position = glm::dvec2(0, 0);

	};
}