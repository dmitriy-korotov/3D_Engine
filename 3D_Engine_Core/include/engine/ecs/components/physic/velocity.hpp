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

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	protected:

		glm::vec3 m_velocity;

	};
}