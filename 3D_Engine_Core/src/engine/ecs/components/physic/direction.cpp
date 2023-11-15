#include <engine/ecs/components/physic/direction.hpp>

#include <engine/Engine.hpp>

#include <glm/geometric.hpp>



namespace engine::ecs::components
{
	direction::direction(const glm::vec3& _direction) noexcept
			: m_direction(glm::normalize(_direction))
	{ }



	void direction::setDirection(const glm::vec3& _direction) noexcept
	{
		m_direction = glm::normalize(_direction);
	}



	const glm::vec3& direction::getDirection() const noexcept
	{
		return m_direction;
	}



	bool direction::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Direction", m_direction, -1.f, 1.f);
	}



	auto direction::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["direction"] = serialized_view_t::array({ m_direction.x, m_direction.y, m_direction.z });

		return serialized_view;
	}



	void direction::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		auto direction_component = _serialized_view.at("direction").begin();

		m_direction.x = *(direction_component);		direction_component++;
		m_direction.y = *(direction_component);		direction_component++;
		m_direction.z = *(direction_component);
	}
}