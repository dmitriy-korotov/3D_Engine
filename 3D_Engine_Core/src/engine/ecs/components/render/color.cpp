#include <engine/ecs/components/render/color.hpp>



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
}