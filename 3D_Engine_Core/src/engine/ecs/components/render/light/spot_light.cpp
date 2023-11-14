#include <engine/ecs/components/render/light/spot_light.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

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



	auto spot_light::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = point_light::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["radius"] = m_radius;

		return serialized_view;
	}



	void spot_light::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		point_light::deserializeFrom(_serialized_view);

		_serialized_view.at("radius").get_to(m_radius);
	}
}