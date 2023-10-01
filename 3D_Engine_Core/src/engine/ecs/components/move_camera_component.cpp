#include <engine/ecs/components/move_camera_component.hpp>



namespace engine::ecs::components
{
	move_camera_component::move_camera_component(const glm::vec3& _velocity, const glm::vec3& _world_velocity) noexcept
			 : m_velocity(_velocity)
			, m_world_velocity(_world_velocity)
	{ }



	void move_camera_component::setVelocity(const glm::vec3& _velocity) noexcept
	{
		m_velocity = _velocity;
	}



	void move_camera_component::setWorldVelocity(const glm::vec3& _world_velocity) noexcept
	{
		m_world_velocity = _world_velocity;
	}



	const glm::vec3& move_camera_component::getVelocity() const noexcept
	{
		return m_velocity;
	}



	const glm::vec3& move_camera_component::getWorldVelocity() const noexcept
	{
		return m_world_velocity;
	}
}