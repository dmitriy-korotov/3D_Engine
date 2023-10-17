#pragma once

#include <engine/ecs/components/physic/velocity.hpp>



namespace engine::ecs::components
{
	class movement_velocity: public velocity
	{
	public:

		static constexpr std::string_view component_name = "movement_velocity";



		movement_velocity(const glm::vec3& _movement_velocity = glm::vec3(0.1f)) noexcept;

		void setVelocityX(float _x_velocity) noexcept;
		void setVelocityY(float _y_velocity) noexcept;
		void setVelocityZ(float _z_velocity) noexcept;

	};
}