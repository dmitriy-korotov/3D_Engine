#include <engine/ecs/components/physic/rotation.hpp>

#include <engine/Engine.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	rotation::rotation(const glm::vec3& _rotation) noexcept
			: m_rotation(_rotation)
	{ }



	void rotation::setRotation(const glm::vec3& _rotation) noexcept
	{
		if (m_rotation != _rotation)
		{
			m_rotation = _rotation;
			m_is_need_update_rotation_matrix = true;
		}
	}



	const glm::vec3& rotation::getRotation() const noexcept
	{
		return m_rotation;
	}



	const glm::mat4& rotation::getRotationMatrix() const noexcept
	{
		if (m_is_need_update_rotation_matrix)
			updateRotationMatrix();
		return m_rotation_matrix;
	}



	void rotation::updateRotationMatrix() const noexcept
	{
		m_rotation_matrix = glm::rotate(glm::mat4(1.f), m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_rotation_matrix = glm::rotate(m_rotation_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_rotation_matrix = glm::rotate(m_rotation_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));

		m_is_need_update_rotation_matrix = false;
	}



	bool rotation::putOnUI() noexcept
	{
		bool is_clicked = Engine::getApplicationUIModule()->putSliderFloat3("Rotation", m_rotation, -360.f, 360.f);
		if (is_clicked)
			m_is_need_update_rotation_matrix = true;
		return is_clicked;
	}
}