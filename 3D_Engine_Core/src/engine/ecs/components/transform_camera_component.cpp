#include <engine/ecs/components/transform_camera_component.hpp>

#include <engine/scene/world_data.hpp>

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	transform_camera_component::transform_camera_component(const glm::vec3& _position, const glm::vec3& _rotation) noexcept
			: m_position(_position)
			, m_rotation(_rotation)
	{ 
		updateViewMatrix();
	}



	void transform_camera_component::setPosition(const glm::vec3& _position) noexcept
	{
		if (m_position != _position)
		{
			m_position = _position;
			m_is_need_update_view_matrix = true;
		}
	}
	void transform_camera_component::setRotation(const glm::vec3& _rotation) noexcept
	{
		if (m_rotation != _rotation)
		{
			m_rotation = _rotation;
			m_is_need_update_view_matrix = true;
		}
	}



	const glm::vec3& transform_camera_component::getPosition() const noexcept
	{
		return m_position;
	}
	const glm::vec3& transform_camera_component::getRotation() const noexcept
	{
		return m_rotation;
	}



	const glm::vec3& transform_camera_component::getForwardDirection() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& transform_camera_component::getRightDirection() const noexcept
	{
		return m_right;
	}
	const glm::vec3& transform_camera_component::getUpDirection() const noexcept
	{
		return m_up;
	}



	void transform_camera_component::moveUp(float _delta) noexcept
	{
		m_position += m_up * _delta;
		m_is_need_update_view_matrix = true;
	}
	void transform_camera_component::moveRight(float _delta) noexcept
	{
		m_position -= m_right * _delta;
		m_is_need_update_view_matrix = true;
	}
	void transform_camera_component::moveForward(float _delta) noexcept
	{
		m_position += m_forward * _delta;
		m_is_need_update_view_matrix = true;
	}



	void transform_camera_component::moveWorldUp(float _delta) noexcept
	{
		m_position += scene::g_world_up_direction * _delta;
		m_is_need_update_view_matrix = true;
	}
	void transform_camera_component::moveWorldRight(float _delta) noexcept
	{
		m_position += scene::g_world_right_direction * _delta;
		m_is_need_update_view_matrix = true;
	}
	void transform_camera_component::moveWorldForward(float _delta) noexcept
	{
		m_position += scene::g_world_forward_direction * _delta;
		m_is_need_update_view_matrix = true;
	}



	const glm::mat4& transform_camera_component::getViewMatrix() noexcept
	{
		if (m_is_need_update_view_matrix)
		{
			updateViewMatrix();
		}
		return m_view_matrix;
	}



	void transform_camera_component::updateViewMatrix() noexcept
	{
		float roll_in_radians =		-glm::radians(m_rotation.x);
		float pitch_in_radians =	-glm::radians(m_rotation.y);
		float yaw_in_radians =		-glm::radians(m_rotation.z);

		glm::mat3 rotate_matrix_x(1.f, 0.f, 0.f,
								  0.f, cos(roll_in_radians), sin(roll_in_radians),
								  0.f, -sin(roll_in_radians), cos(roll_in_radians));

		glm::mat3 rotate_matrix_y(cos(pitch_in_radians), 0.f, -sin(pitch_in_radians),
								  0.f, 1.f, 0.f,
								  sin(pitch_in_radians), 0.f, cos(pitch_in_radians));

		glm::mat3 rotate_matrix_z(glm::cos(yaw_in_radians), glm::sin(yaw_in_radians), 0.f,
								  -glm::sin(yaw_in_radians), glm::cos(yaw_in_radians), 0.f,
								  0.f, 0.f, 1.f);
		
		glm::mat3 euler_rotate_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x;

		m_forward = glm::normalize(euler_rotate_matrix * scene::g_world_forward_direction);
		m_right = glm::normalize(euler_rotate_matrix * scene::g_world_right_direction);
		m_up = glm::normalize(glm::cross(m_forward, m_right));

		m_view_matrix = glm::lookAt(m_position, m_position + m_forward, m_up);

		m_is_need_update_view_matrix = false;
	}
}