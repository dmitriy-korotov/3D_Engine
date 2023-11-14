#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec4.hpp>



namespace engine::ecs::components
{
	class color: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "color";



		color(const glm::vec4 _color = glm::vec4(1.f)) noexcept;

		void setColor(const glm::vec4 _color) noexcept;
		const glm::vec4& getColor() const noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		glm::vec4 m_color;

	};
}