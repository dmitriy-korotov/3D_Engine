#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class camera_transform_component
	{
	public:

		static constexpr std::string_view component_name = "camera_transform_component";

		camera_transform_component(const glm::vec3& _position = glm::vec3(0.f), const glm::vec3& _rotation = glm::vec3(0.f)) noexcept;

		void setPosition(const glm::vec3& _position) noexcept;
		void setRotation(const glm::vec3& _rotation) noexcept;

		const glm::vec3& getPosition() const noexcept;
		const glm::vec3& getRotation() const noexcept;

		const glm::vec3& getForwardDirection() const noexcept;
		const glm::vec3& getRightDirection() const noexcept;
		const glm::vec3& getUpDirection() const noexcept;

		void moveUp(float _delta) noexcept;
		void moveRight(float _delta) noexcept;
		void moveForward(float _delta) noexcept;

		void moveWorldUp(float _delta) noexcept;
		void moveWorldRight(float _delta) noexcept;
		void moveWorldForward(float _delta) noexcept;

		const glm::mat4& getViewMatrix() noexcept;

	private:

		void updateViewMatrix() noexcept;

	private:

		glm::vec3 m_position;
		glm::vec3 m_rotation;

		glm::vec3 m_forward = glm::vec3(1.f, 0.f, 0.f);
		glm::vec3 m_right =	  glm::vec3(0.f, -1.f, 0.f);
		glm::vec3 m_up =	  glm::vec3(0.f, 0.f, 1.f);

		glm::mat4 m_view_matrix = glm::mat4(1.f);
		bool m_is_need_update_view_matrix = true;

	};
}