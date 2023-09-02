#pragma once

#include <glm/vec3.hpp>						// glm dependens (TODO: try to remove)
#include <glm/ext/matrix_float4x4.hpp>



namespace engine::render
{
	class camera
	{
	public:

		enum class Projection : uint8_t
		{
			Perspective,
			Orthographic
		};

		explicit camera(const glm::vec3& _position = glm::vec3(0.f), const glm::vec3& _rotation = glm::vec3(0.f),
						Projection _projection_mode = Projection::Perspective) noexcept;

		void setProjectionMode(Projection _projection_mode) noexcept;
		void setPosition(const glm::vec3& _position) noexcept;
		void setRotation(const glm::vec3& _rotation) noexcept;
		void setPositionAndRotation(const glm::vec3& _position, const glm::vec3& _rotation) noexcept;

		const glm::mat4& getViewMatrix() const noexcept;
		const glm::mat4& getProjectionMatrix() const noexcept;
		glm::mat4 getViewProjectionMatrix() const noexcept;

	private:

		void updateViewMatrix() noexcept;
		void updateProjectionMatrix() noexcept;

	private:

		glm::vec3 m_position_;
		glm::vec3 m_rotation_;

		Projection m_projection_mode;

		glm::mat4 m_view_matrix;
		glm::mat4 m_projection_matrix;

	};
}