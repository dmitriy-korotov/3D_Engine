#include <engine/scene/components/render/color.hpp>

#include <engine/Engine.hpp>



namespace engine::scene::components
{
	color::color(const glm::vec4 _color) noexcept
			: m_color(_color)
	{ }

	
	
	auto color::setColor(const glm::vec4 _color) noexcept -> void
	{
		m_color = _color;
	}



	auto color::getColor() const noexcept -> const glm::vec4&
	{
		return m_color;
	}



	auto color::putOnUI() noexcept -> bool
	{
		return Engine::getApplicationUIModule()->putColorEdit4("Color", m_color);
	}



	auto color::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["color"] = serialized_view_t::array({ m_color.r, m_color.g, m_color.b, m_color.a });

		return serialized_view;
	}



	auto color::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		auto color_component = _serialized_view.at("color").begin();

		m_color.r = *(color_component);		color_component++;
		m_color.g = *(color_component);		color_component++;
		m_color.b = *(color_component);		color_component++;
		m_color.a = *(color_component);
	}
}