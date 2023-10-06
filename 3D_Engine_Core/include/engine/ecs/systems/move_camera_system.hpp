#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <glm/vec2.hpp>



namespace engine::ecs::components
{
	class camera_transform;
	class velocity;
}



namespace engine::ecs::systems
{
	using components::camera_transform;
	using components::velocity;

	class move_camera_system : public basic_system
	{
	public:

		void update(float _delta_time) const noexcept override;

	private:

		void translateCamera(camera_transform& _transform_component, 
							 velocity& _move_component, float _delta_time) const noexcept;
		void rotateCamera(camera_transform& _transform_component,
						  velocity& _move_component, float _delta_time) const noexcept;

	private:

		mutable glm::dvec2 m_last_cursor_position = glm::dvec2(0, 0);

	};
}