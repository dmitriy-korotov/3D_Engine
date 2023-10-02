#include <engine/ecs/components/camera_transform_component.hpp>

#include <engine/scene/world_data.hpp>

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	camera_transform_component::camera_transform_component(const glm::vec3& _position, const glm::vec3& _rotation) noexcept
			: m_position(_position)
			, m_rotation(_rotation)
	{ 
		updateViewMatrix();
	}



	void camera_transform_component::setPosition(const glm::vec3& _position) noexcept
	{
		if (m_position != _position)
		{
			m_position = _position;
			m_is_need_update_view_matrix = true;
		}
	}
	void camera_transform_component::setRotation(const glm::vec3& _rotation) noexcept
	{
		if (m_rotation != _rotation)
		{
			m_rotation = _rotation;
			m_is_need_update_view_matrix = true;
		}
	}



	const glm::vec3& camera_transform_component::getPosition() const noexcept
	{
		return m_position;
	}
	const glm::vec3& camera_transform_component::getRotation() const noexcept
	{
		return m_rotation;
	}



	const glm::vec3& camera_transform_component::getForwardDirection() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& camera_transform_component::getRightDirection() const noexcept
	{
		return m_right;
	}
	const glm::vec3& camera_transform_component::getUpDirection() const noexcept
	{
		return m_up;
	}



	void camera_transform_component::moveUp(float _delta) noexcept
	{
		m_position += m_up * _delta;
		m_is_need_update_view_matrix = true;
	}
	void camera_transform_component::moveRight(float _delta) noexcept
	{
		m_position -= m_right * _delta;
		m_is_need_update_view_matrix = true;
	}
	void camera_transform_component::moveForward(float _delta) noexcept
	{
		m_position += m_forward * _delta;
		m_is_need_update_view_matrix = true;
	}



	void camera_transform_component::moveWorldUp(float _delta) noexcept
	{
		m_position += scene::g_world_up_direction * _delta;
		m_is_need_update_view_matrix = true;
	}
	void camera_transform_component::moveWorldRight(float _delta) noexcept
	{
		m_position += scene::g_world_right_direction * _delta;
		m_is_need_update_view_matrix = true;
	}
	void camera_transform_component::moveWorldForward(float _delta) noexcept
	{
		m_position += scene::g_world_forward_direction * _delta;
		m_is_need_update_view_matrix = true;
	}



	const glm::mat4& camera_transform_component::getViewMatrix() noexcept
	{
		if (m_is_need_update_view_matrix)
		{
			updateViewMatrix();
		}
		return m_view_matrix;
	}



	void camera_transform_component::updateViewMatrix() noexcept
	{
		float roll_in_radians = glm::radians(m_rotation.x);
		float pitch_in_radians = glm::radians(m_rotation.y);
		float yaw_in_radians = glm::radians(m_rotation.z);

		glm::mat4 euler_rotate_matrix(1.f);
		euler_rotate_matrix = glm::rotate(euler_rotate_matrix, -roll_in_radians, glm::vec3(1.f, 0.f, 0.f));
		euler_rotate_matrix = glm::rotate(euler_rotate_matrix, -pitch_in_radians, glm::vec3(0.f, 1.f, 0.f));
		euler_rotate_matrix = glm::rotate(euler_rotate_matrix, -yaw_in_radians, glm::vec3(0.f, 0.f, 1.f));

		m_forward = glm::normalize(glm::mat3(euler_rotate_matrix) * scene::g_world_forward_direction);
		m_right = glm::normalize(glm::mat3(euler_rotate_matrix) * scene::g_world_right_direction);
		m_up = glm::normalize(glm::cross(m_forward, m_right));

		m_view_matrix = glm::lookAt(m_position, m_position + m_forward, m_up);

		m_is_need_update_view_matrix = false;
	}
}