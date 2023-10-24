#pragma once

#include <engine/ecs/components/physic/velocity.hpp>



namespace engine::ecs::components
{
	class rotate_velocity: public velocity
	{
	public:

		static constexpr std::string_view component_name = "rotate_velocity";



		rotate_velocity(const glm::vec3& _rotate_velocity = glm::vec3(1.f)) noexcept;

		void setVelocityRoll(float _roll_velocity) noexcept;
		void setVelocityPitch(float _pitch_velocity) noexcept;
		void setVelocityYaw(float _yaw_velocity) noexcept;

	};
}