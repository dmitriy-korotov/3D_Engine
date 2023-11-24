#include <engine/scene/components/physic/direction.hpp>

#include <engine/Engine.hpp>

#include <glm/geometric.hpp>



namespace engine::scene::components
{
	direction::direction(const glm::vec3& _direction) noexcept
			: m_direction(glm::normalize(_direction))
	{ }



	auto direction::setDirection(const glm::vec3& _direction) noexcept -> void
	{
		m_direction = glm::normalize(_direction);
	}



	auto direction::getDirection() const noexcept -> const glm::vec3&
	{
		return m_direction;
	}



	auto direction::putOnUI() noexcept -> bool
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Direction", m_direction, -1.f, 1.f);
	}



	auto direction::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["direction"] = serialized_view_t::array({ m_direction.x, m_direction.y, m_direction.z });

		return serialized_view;
	}



	auto direction::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		auto direction_component = _serialized_view.at("direction").begin();

		m_direction.x = *(direction_component);		direction_component++;
		m_direction.y = *(direction_component);		direction_component++;
		m_direction.z = *(direction_component);
	}
}