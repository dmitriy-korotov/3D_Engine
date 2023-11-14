#include <engine/ecs/components/render/color.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	color::color(const glm::vec4 _color) noexcept
			: m_color(_color)
	{ }

	
	
	void color::setColor(const glm::vec4 _color) noexcept
	{
		m_color = _color;
	}



	const glm::vec4& color::getColor() const noexcept
	{
		return m_color;
	}



	bool color::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putColorEdit4("Color", m_color);
	}



	auto color::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["color"] = serialized_view_t::array({ m_color.r, m_color.g, m_color.b, m_color.a });

		return serialized_view;
	}



	void color::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		auto color_component = _serialized_view.at("color").begin();

		m_color.r = *(color_component);		color_component++;
		m_color.g = *(color_component);		color_component++;
		m_color.b = *(color_component);		color_component++;
		m_color.a = *(color_component);
	}
}