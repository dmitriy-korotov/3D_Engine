#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class direction: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "direction";



		direction(const glm::vec3& _direction = glm::vec3(0.f, 0.f, -1.f)) noexcept;

		void setDirection(const glm::vec3& _direction) noexcept;

		const glm::vec3& getDirection() const noexcept;

	protected:

		glm::vec3 m_direction;

	};
}