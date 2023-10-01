#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/ext/vector_float3.hpp>



namespace engine::ecs::components
{
	class transform_component: public basic_component
	{
	public:

		transform_component(glm::vec3 _position = glm::vec3(0.f),
							glm::vec3 _rotation = glm::vec3(0.f),
							glm::vec3 _scale = glm::vec3(1.f)) noexcept;

		void setTransform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) noexcept;

		const glm::vec3 getPosition() const noexcept;
		const glm::vec3 getRotation() const noexcept;
		const glm::vec3 getScale() const noexcept;

	private:

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

	};
}