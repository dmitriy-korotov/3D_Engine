#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class rotation:	public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "rotation";

		rotation(const glm::vec3& _rotation = glm::vec3(0.f)) noexcept;

		void setRotation(const glm::vec3& _rotation) noexcept;
		const glm::vec3& getRotation() const noexcept;

	protected:

		glm::vec3 m_rotation;

	};
}