#include <engine/scene/components/physic/velocity.hpp>

#include <engine/Engine.hpp>



namespace engine::scene::components
{
	velocity::velocity(const glm::vec3& _velocity) noexcept
			: m_velocity(_velocity)
	{ }



	auto velocity::setVelocity(const glm::vec3& _velocity) noexcept -> void
	{
		m_velocity = _velocity;
	}



	auto velocity::getVelocity() const noexcept -> const glm::vec3&
	{
		return m_velocity;
	}



	auto velocity::putOnUI() noexcept -> bool
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Velocity", m_velocity, 0.f, 1.f);
	}



	auto velocity::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["velocity"] = serialized_view_t::array({ m_velocity.x, m_velocity.y, m_velocity.z });

		return serialized_view;
	}



	auto velocity::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		auto valocity_component = _serialized_view.at("velocity").begin();

		m_velocity.x = *(valocity_component);		valocity_component++;
		m_velocity.y = *(valocity_component);		valocity_component++;
		m_velocity.z = *(valocity_component);
	}
}