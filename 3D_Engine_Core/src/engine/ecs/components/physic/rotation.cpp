#include <engine/ecs/components/physic/rotation.hpp>



namespace engine::ecs::components
{
	rotation::rotation(const glm::vec3& _rotation) noexcept
			: m_rotation(_rotation)
	{ }



	void rotation::setRotation(const glm::vec3& _rotation) noexcept
	{
		m_rotation = _rotation;
	}



	const glm::vec3& rotation::getRotation() const noexcept
	{
		return m_rotation;
	}
}