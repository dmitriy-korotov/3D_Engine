#pragma once

#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::components
{
	class rotate: public basic_component
	{
	public:

		static constexpr std::string_view component_name = "rotate";

		rotate() = default;

		void rotateX(float _delta_angle) const noexcept;
		void rotateY(float _delta_angle) const noexcept;
		void rotateZ(float _delta_angle) const noexcept;

	};
}