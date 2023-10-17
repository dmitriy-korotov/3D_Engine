#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class orientation: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "orientation";

		orientation() = default;
		orientation(const glm::vec3& _forward, const glm::vec3& _right) noexcept;

		void setOrientation(const glm::vec3& _forward, const glm::vec3& _right) noexcept;

		const glm::vec3& getForward() const noexcept;
		const glm::vec3& getRight() const noexcept;
		const glm::vec3& getUp() const noexcept;

		bool putOnUI() noexcept override;

	protected:

		glm::vec3 m_forward = glm::vec3(1.f, 0.f, 0.f);
		glm::vec3 m_right =	  glm::vec3(0.f, -1.f, 0.f);
		glm::vec3 m_up =	  glm::vec3(0.f, 0.f, 1.f);

	};
}