#include <engine/ecs/components/render/light/spot_light.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/physic/direction.hpp>



namespace engine::ecs::components
{
	spot_light::spot_light(float _radius) noexcept
			: m_radius(_radius)
	{ }



	const glm::vec3& spot_light::getDirection() const noexcept
	{
		return ECS::instance().getComponentsManager()->getComponent<direction>(getOwner())->getDirection();
	}



	void spot_light::setRadius(float _radius) noexcept
	{
		m_radius = _radius;
	}



	float spot_light::getRadius() const noexcept
	{
		return m_radius;
	}
}