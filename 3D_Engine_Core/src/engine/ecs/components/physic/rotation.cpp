#include <engine/ecs/components/physic/rotation.hpp>

#include <engine/Engine.hpp>



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



	bool rotation::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Rotation", m_rotation, -360.f, 360.f);
	}
}