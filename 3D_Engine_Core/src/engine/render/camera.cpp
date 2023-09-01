#include <engine/render/camera.hpp>

#include <glm/trigonometric.hpp>



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



	void camera::updateViewMatrix() noexcept
	{
		glm::mat4 translate_matrix(1.f,				 0.f,				0.f,				0.f,
								   0.f,				 1.f,				0.f,				0.f,
								   0.f,				 0.f,				1.f,				0.f,
								   -m_position_.x,	 -m_position_.y,	-m_position_.z,		1.f);



		float rotate_in_redians_x = glm::radians(-m_rotation_.x);
		glm::mat4 rotate_matrix_x(1.f,		0.f,							0.f,							0.f,
								  0.f,		cos(rotate_in_redians_x),		sin(rotate_in_redians_x),		0.f,
								  0.f,		-sin(rotate_in_redians_x),		cos(rotate_in_redians_x),		0.f,
								  0.f,		0.f,							0.f,							1.f);



		float rotate_in_redians_y = glm::radians(-m_rotation_.y);
		glm::mat4 rotate_matrix_y(cos(rotate_in_redians_y),		 0.f,		 -sin(rotate_in_redians_y),		 0.f,
								  0.f,							 1.f,		 0.f,							 0.f,
								  sin(rotate_in_redians_y),		 0.f,		 cos(rotate_in_redians_y),		 0.f,
								  0.f,							 0.f,		 0.f,							 1.f);



		float rotate_in_redians_z = glm::radians(-m_rotation_.z);
		glm::mat4 rotate_matrix_z(glm::cos(rotate_in_redians_z),	glm::sin(rotate_in_redians_z),		0.f,	 0.f,
								  -glm::sin(rotate_in_redians_z),	glm::cos(rotate_in_redians_z),		0.f,	 0.f,
								  0.f,								0.f,								1.f,	 0.f,
								  0.f,								0.f,								0.f,	 1.f);


		m_view_matrix = rotate_matrix_y * rotate_matrix_x * translate_matrix;
	}



	void camera::updateProjectionMatrix() noexcept
	{
		if (m_projection_mode == Projection::Perspective)
		{
			float r = 0.1f;
			float t = 0.1f;
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