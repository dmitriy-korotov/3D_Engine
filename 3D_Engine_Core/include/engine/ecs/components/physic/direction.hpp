#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class direction: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "direction";

		direction() = default;
		direction(const glm::vec3& _forward, const glm::vec3& _right, const glm::vec3& _up) noexcept;

		void setForward(const glm::vec3& _forward) noexcept;
		void setRight(const glm::vec3& _right) noexcept;
		void setUp(const glm::vec3& _up) noexcept;

		const glm::vec3& getForward() const noexcept;
		const glm::vec3& getRight() const noexcept;
		const glm::vec3& getUp() const noexcept;

	protected:

		glm::vec3 m_forward = glm::vec3(1.f, 0.f, 0.f);
		glm::vec3 m_right =	  glm::vec3(0.f, -1.f, 0.f);
		glm::vec3 m_up =	  glm::vec3(0.f, 0.f, 1.f);

	};
}