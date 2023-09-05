#include <engine/render/camera.hpp>

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>



namespace engine::render
{
	camera::camera(const glm::vec3& _position, const glm::vec3& _rotation, Projection _projection_mode) noexcept
		: m_position_(_position)
		, m_rotation_(_rotation)
		, m_projection_mode(_projection_mode)
	{
		updateViewMatrix();
		updateProjectionMatrix();
	}



	void camera::setProjectionMode(Projection _projection_mode) noexcept
	{
		m_projection_mode = _projection_mode;
		updateProjectionMatrix();
	}



	void camera::setPosition(const glm::vec3& _position) noexcept
	{
		m_position_ = _position;
		updateViewMatrix();
	}



	void camera::setRotation(const glm::vec3& _rotation) noexcept
	{
		m_rotation_ = _rotation;
		updateViewMatrix();
	}



	void camera::setPositionAndRotation(const glm::vec3& _position, const glm::vec3& _rotation) noexcept
	{
		m_position_ = _position;
		m_rotation_ = _rotation;
		updateViewMatrix();
	}



	const glm::mat4& camera::getViewMatrix() const noexcept
	{
		return m_view_matrix;
	}



	const glm::mat4& camera::getProjectionMatrix() const noexcept
	{
		return m_projection_matrix;
	}



	glm::mat4 camera::getViewProjectionMatrix() const noexcept
	{
		return m_projection_matrix * m_view_matrix;
	}



	void camera::moveForward(float _delta) noexcept
	{
		m_position_ += m_direction_ * _delta;
		updateViewMatrix();
	}



	void camera::moveRight(float _delta) noexcept
	{
		m_position_ += m_right_ * _delta;
		updateViewMatrix();
	}



	void camera::moveUp(float _delta) noexcept
	{
		m_position_ += m_up_ * _delta;
		updateViewMatrix();
	}



	void camera::moveAndRotate(const glm::vec3& _movement_delta, const glm::vec3& _rotation_delta) noexcept
	{
		m_position_ += m_direction_ * _movement_delta.x;
		m_position_ += m_right_ * _movement_delta.y;
		m_position_ += m_up_ * _movement_delta.z;

		m_rotation_ += _rotation_delta;

		updateViewMatrix();
	}



	void camera::updateViewMatrix() noexcept
	{
		float roll_in_radians	= glm::radians(m_rotation_.x);
		float pitch_in_radians	= glm::radians(m_rotation_.y);
		float yaw_in_radians	= glm::radians(m_rotation_.z);



		glm::mat3 rotate_matrix_x(1.f,		0.f,							0.f,			
								  0.f,		cos(roll_in_radians),			sin(roll_in_radians),
								  0.f,		-sin(roll_in_radians),			cos(roll_in_radians));

		glm::mat3 rotate_matrix_y(cos(pitch_in_radians),		 0.f,		 -sin(pitch_in_radians),
								  0.f,							 1.f,		 0.f,					
								  sin(pitch_in_radians),		 0.f,		 cos(pitch_in_radians));

		glm::mat3 rotate_matrix_z(glm::cos(yaw_in_radians),		glm::sin(yaw_in_radians),		0.f,
								  -glm::sin(yaw_in_radians),	glm::cos(yaw_in_radians),		0.f,
								  0.f,								0.f,						1.f);



		glm::mat3 euler_rotate_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x;

		m_direction_ = glm::normalize(euler_rotate_matrix * s_world_forward);
		m_right_ = glm::normalize(euler_rotate_matrix * s_world_right);
		m_up_ = glm::cross(m_right_, m_direction_);

		m_view_matrix = glm::lookAt(m_position_, m_direction_, m_up_);
	}



	void camera::updateProjectionMatrix() noexcept
	{
		if (m_projection_mode == Projection::Perspective)
		{
			float r = 0.1f;
			float t = 0.1f;			// TODO: added posibility set this camera parametrs
			float f = 10.f;
			float n = 0.1f;

			m_projection_matrix = glm::mat4(n / r,		0.f,		0.f,						0.f,
											0.f,		n / t,		0.f,						0.f,
											0.f,		0.f,		(-f - n) / (f - n),			-1.f,
											0.f,		0.f,		-2.f * f * n / (f - n),		0.f);
		}
		else
		{
			float r = 2.f;
			float t = 2.f;
			float f = 100.f;
			float n = 0.1f;

			m_projection_matrix = glm::mat4(1.f / r,	0.f,		 0.f,						0.f,
											0.f,		1.f / t,	 0.f,						0.f,
											0.f,		0.f,		 -2.f / (f - n),			0.f,
											0.f,		0.f,		 (-f - n) / (f - n),		1.f);
		}
	}
}