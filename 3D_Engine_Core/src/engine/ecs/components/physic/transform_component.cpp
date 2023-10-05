#include <engine/ecs/components/physic/transform_component.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	transform_component::transform_component(const glm::vec3& _position, const glm::vec3& _rotation, const glm::vec3& _scale) noexcept
			: position(_position)
			, rotation(_rotation)
			, scale(_scale)
	{
		updateModelMatrix();
	}



	void transform_component::setTransform(const glm::vec3& _position, const glm::vec3& _rotation, const glm::vec3& _scale) noexcept
	{
		if (m_position != _position || m_rotation != _rotation || m_scale != _scale)
		{
			position::setPosition(_position);
			rotation::setRotation(_rotation);
			scale::setScale(_scale);
			m_is_need_update_model_matrix = true;
		}
	}



	void transform_component::setPosition(const glm::vec3& _position) noexcept
	{
		if (m_position != _position)
		{
			position::setPosition(_position);
			m_is_need_update_model_matrix = true;
		}
	}



	void transform_component::setRotation(const glm::vec3& _rotation) noexcept
	{
		if (m_rotation != _rotation)
		{
			rotation::setRotation(_rotation);
			m_is_need_update_model_matrix = true;
		}
	}



	void transform_component::setScale(const glm::vec3& _scale) noexcept
	{
		if (m_scale != _scale)
		{
			scale::setScale(_scale);
			m_is_need_update_model_matrix = true;
		}
	}



	const glm::mat4& transform_component::getModelMatrix() noexcept
	{
		if (m_is_need_update_model_matrix)
		{
			updateModelMatrix();
		}
		return m_model_matrix;
	}



	glm::mat3 transform_component::getNormalMatrix() noexcept
	{
		if (m_is_need_update_model_matrix)
		{
			updateModelMatrix();
		}
		return glm::mat3(glm::transpose(glm::inverse(m_model_matrix)));
	}



	void transform_component::updateModelMatrix() noexcept
	{
		m_model_matrix = glm::mat4(1.f);
		m_model_matrix = glm::scale(m_model_matrix, m_scale);
		m_model_matrix = glm::rotate(m_model_matrix, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_model_matrix = glm::rotate(m_model_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_model_matrix = glm::rotate(m_model_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));
		m_model_matrix = glm::translate(m_model_matrix, m_position);

		m_is_need_update_model_matrix = false;
	}



	const glm::vec3& transform_component::getPosition() const noexcept
	{
		return m_position;
	}



	const glm::vec3& transform_component::getRotation() const noexcept
	{
		return m_rotation;
	}



	const glm::vec3& transform_component::getScale() const noexcept
	{
		return m_scale;
	}
}