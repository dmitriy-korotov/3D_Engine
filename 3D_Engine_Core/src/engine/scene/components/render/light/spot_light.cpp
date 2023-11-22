#include <engine/scene/components/render/light/spot_light.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/physic/direction.hpp>



namespace engine::scene::components
{
	spot_light::spot_light(float _radius) noexcept
			: m_radius(_radius)
	{ }



	auto spot_light::getDirection() const noexcept -> const glm::vec3&
	{
		return Scene::getComponent<direction>(getOwner())->getDirection();
	}



	auto spot_light::setRadius(float _radius) noexcept -> void
	{
		m_radius = _radius;
	}



	auto spot_light::getRadius() const noexcept -> float
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



	auto spot_light::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		point_light::deserializeFrom(_serialized_view);

		_serialized_view.at("radius").get_to(m_radius);
	}
}