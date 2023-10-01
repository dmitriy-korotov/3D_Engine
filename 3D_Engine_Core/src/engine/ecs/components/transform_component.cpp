#include <engine/ecs/components/transform_component.hpp>



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