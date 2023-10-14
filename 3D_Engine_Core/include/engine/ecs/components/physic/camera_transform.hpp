#pragma once

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/direction.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class camera_transform: public position,
							public rotation,
							public direction
						
	{
	public:

		static constexpr std::string_view component_name = "camera_transform";

		camera_transform(const glm::vec3& _position = glm::vec3(0.f), const glm::vec3& _rotation = glm::vec3(0.f)) noexcept;

		void setPosition(const glm::vec3& _position) noexcept;
		void setRotation(const glm::vec3& _rotation) noexcept;

		void moveUp(float _delta) noexcept;
		void moveRight(float _delta) noexcept;
		void moveForward(float _delta) noexcept;

		void moveWorldUp(float _delta) noexcept;
		void moveWorldRight(float _delta) noexcept;
		void moveWorldForward(float _delta) noexcept;

		const glm::mat4& getViewMatrix() noexcept;

		bool putOnUI() noexcept override;

	private:

		void updateViewMatrix() noexcept;

	private:

		glm::mat4 m_view_matrix = glm::mat4(1.f);
		bool m_is_need_update_view_matrix = true;

	};
}