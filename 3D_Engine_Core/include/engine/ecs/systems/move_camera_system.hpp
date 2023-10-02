#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <glm/vec2.hpp>



namespace engine::ecs::components
{
	class transform_camera_component;
	class move_camera_component;
}



namespace engine::ecs::systems
{
	using components::transform_camera_component;
	using components::move_camera_component;

	class move_camera_system : public basic_system
	{
	public:

		void update(float _delta_time) const noexcept override;

	private:

		void translateCamera(transform_camera_component& _transform_component, 
							 move_camera_component& _move_component, float _delta_time) const noexcept;
		void rotateCamera(transform_camera_component& _transform_component,
						  move_camera_component& _move_component, float _delta_time) const noexcept;

	private:

		mutable glm::dvec2 m_last_cursor_position = glm::dvec2(0, 0);

	};
}