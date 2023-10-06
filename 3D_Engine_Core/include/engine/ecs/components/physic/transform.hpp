#pragma once

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/scale.hpp>

#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class transform: public position,
				     public rotation,
					 public scale
	{
	public:

		static constexpr std::string_view component_name = "transform";



		transform(const glm::vec3& _position = glm::vec3(0.f),
				  const glm::vec3& _rotation = glm::vec3(0.f),
				  const glm::vec3& _scale = glm::vec3(1.f)) noexcept;

		void setTransform(const glm::vec3& _position, const glm::vec3& _rotation, const glm::vec3& _scale) noexcept;
		void setPosition(const glm::vec3& _position) noexcept;
		void setRotation(const glm::vec3& _rotation) noexcept;
		void setScale(const glm::vec3& _scale) noexcept;

		const glm::mat4& getModelMatrix() const noexcept;
		glm::mat3 getNormalMatrix() const noexcept;

		const glm::vec3& getPosition() const noexcept;
		const glm::vec3& getRotation() const noexcept;
		const glm::vec3& getScale() const noexcept;

	private:

		void updateModelMatrix() const noexcept;

	private:

		mutable glm::mat4 m_model_matrix = glm::mat4(1.f);
		mutable bool m_is_need_update_model_matrix = true;

	};
}