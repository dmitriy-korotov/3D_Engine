#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class move_camera_component: public basic_component
	{
	public:

		static constexpr std::string_view component_name = "move_camera_component";

		move_camera_component(const glm::vec3& _velocity = glm::vec3(0.003f), const glm::vec3& _world_velocity = glm::vec3(0.003f)) noexcept;

		void setVelocity(const glm::vec3& _velocity) noexcept;
		void setWorldVelocity(const glm::vec3& _world_velocity) noexcept;

		const glm::vec3& getVelocity() const noexcept;
		const glm::vec3& getWorldVelocity() const noexcept;

	private:

		glm::vec3 m_velocity;
		glm::vec3 m_world_velocity;

	};
}