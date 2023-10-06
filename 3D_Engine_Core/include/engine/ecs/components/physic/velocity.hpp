#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class velocity: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "velocity";

		velocity(const glm::vec3& _velocity = glm::vec3(0.005f)) noexcept;

		void setVelocity(const glm::vec3& _velocity) noexcept;
		const glm::vec3& getVelocity() const noexcept;

	protected:

		glm::vec3 m_velocity;

	};
}