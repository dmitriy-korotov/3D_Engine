#include <engine/ecs/components/transform_component.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	transform_component::transform_component(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) noexcept
			: m_position(std::move(_position))
			, m_rotation(std::move(_rotation))
			, m_scale(_scale)
	{ }



	void transform_component::setTransform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) noexcept
	{
		m_position = std::move(_position);
		m_rotation = std::move(_rotation);
		m_scale = std::move(_scale);
	}



	glm::mat4 transform_component::getModelMatrix() const noexcept
	{
		glm::mat4 model_matrix(1.f);
		model_matrix = glm::scale(model_matrix, m_scale);
		model_matrix = glm::rotate(model_matrix, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		model_matrix = glm::rotate(model_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		model_matrix = glm::rotate(model_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));
		model_matrix = glm::translate(model_matrix, m_position);
		return model_matrix;
	}



	const glm::vec3 transform_component::getPosition() const noexcept
	{
		return m_position;
	}



	const glm::vec3 transform_component::getRotation() const noexcept
	{
		return m_rotation;
	}



	const glm::vec3 transform_component::getScale() const noexcept
	{
		return m_scale;
	}
}