#include <engine/render/camera.hpp>

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>



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
		m_is_needed_update_projection_matrix = true;
	}



	void camera::setPosition(const glm::vec3& _position) noexcept
	{
		m_position_ = _position;
		m_is_needed_update_view_matrix = true;
	}



	void camera::setRotation(const glm::vec3& _rotation) noexcept
	{
		m_rotation_ = _rotation;
		m_is_needed_update_view_matrix = true;
	}



	void camera::setPositionAndRotation(const glm::vec3& _position, const glm::vec3& _rotation) noexcept
	{
		m_position_ = _position;
		m_rotation_ = _rotation;
		m_is_needed_update_view_matrix = true;
	}




	void camera::setNearPlane(float _distance_to_near_plane) noexcept
	{
		m_near_plane = _distance_to_near_plane;
		m_is_needed_update_projection_matrix = true;
	}



	void camera::setFarPlane(float _distance_to_far_plane) noexcept
	{
		m_far_plane = _distance_to_far_plane;
		m_is_needed_update_projection_matrix = true;
	}



	void camera::setFieldOfView(float _fov) noexcept
	{
		m_field_of_view = _fov;
		m_is_needed_update_projection_matrix = true;
	}



	void camera::setViewPortSize(float _width, float _height) noexcept
	{
		m_view_port_size = glm::vec2(_width, _height);
		m_is_needed_update_projection_matrix = true;
	}



	float camera::getNearPlane() const noexcept
	{
		return m_near_plane;
	}



	float camera::getFarPlane() const noexcept
	{
		return m_far_plane;
	}



	float camera::getFieldOfView() const noexcept
	{
		return m_field_of_view;
	}


	
	const glm::vec3& camera::getPosition() const noexcept
	{
		return m_position_;
	}



	const glm::vec3& camera::getRotation() const noexcept
	{
		return m_rotation_;
	}



	const glm::mat4& camera::getViewMatrix() noexcept
	{
		if (m_is_needed_update_view_matrix)
		{
			updateViewMatrix();
		}
		return m_view_matrix;
	}



	const glm::mat4& camera::getProjectionMatrix() noexcept
	{
		if (m_is_needed_update_projection_matrix)
		{
			updateProjectionMatrix();
		}
		return m_projection_matrix;
	}



	glm::mat4 camera::getViewProjectionMatrix() noexcept
	{
		return getProjectionMatrix() * getViewMatrix();
	}



	void camera::moveForward(float _delta) noexcept
	{
		m_position_ += m_direction_ * _delta;
		m_is_needed_update_view_matrix = true;
	}



	void camera::moveRight(float _delta) noexcept
	{
		m_position_ += m_right_ * _delta;
		m_is_needed_update_view_matrix = true;
	}



	void camera::moveUp(float _delta) noexcept
	{
		m_position_ += m_up_ * _delta;
		m_is_needed_update_view_matrix = true;
	}



	void camera::moveWorldForward(float _delta) noexcept
	{
		m_position_ += s_world_forward * _delta;
		m_is_needed_update_view_matrix = true;
	}



	void camera::moveWorldRight(float _delta) noexcept
	{
		m_position_ += s_world_right * _delta;
		m_is_needed_update_view_matrix = true;
	}



	void camera::moveWorldUp(float _delta) noexcept
	{
		m_position_ += s_world_up * _delta;
		m_is_needed_update_view_matrix = true;
	}



	void camera::moveAndRotate(const glm::vec3& _movement_delta, const glm::vec3& _rotation_delta) noexcept
	{
		m_position_ += m_direction_ * _movement_delta.x;
		m_position_ += m_right_ * _movement_delta.y;
		m_position_ += m_up_ * _movement_delta.z;

		m_rotation_ += _rotation_delta;

		m_is_needed_update_view_matrix = true;
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

		m_view_matrix = glm::lookAt(m_position_, m_position_ + m_direction_, m_up_);

		m_is_needed_update_view_matrix = false;
	}



	void camera::updateProjectionMatrix() noexcept
	{
		if (m_projection_mode == Projection::Perspective)
		{
			/*float r = 0.1f;
			float t = 0.1f;			
			float f = 100.f;
			float n = 0.1f;

			m_projection_matrix = glm::mat4(n / r,		0.f,		0.f,						0.f,
											0.f,		n / t,		0.f,						0.f,
											0.f,		0.f,		(-f - n) / (f - n),			-1.f,
											0.f,		0.f,		-2.f * f * n / (f - n),		0.f);*/
			m_projection_matrix = glm::perspective(glm::radians(m_field_of_view), m_view_port_size.x / m_view_port_size.y, m_near_plane, m_far_plane);
		}
		else
		{
			float r = 2.f;
			float t = 2.f;				// TODO: added posibility set this camera parametrs
			float f = 100.f;
			float n = 0.1f;

			m_projection_matrix = glm::mat4(1.f / r,	0.f,		 0.f,						0.f,
											0.f,		1.f / t,	 0.f,						0.f,
											0.f,		0.f,		 -2.f / (f - n),			0.f,
											0.f,		0.f,		 (-f - n) / (f - n),		1.f);
		}
		m_is_needed_update_projection_matrix = false;
	}
}