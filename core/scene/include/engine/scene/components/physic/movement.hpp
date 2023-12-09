#pragma once

#include <engine/scene/Scene.hpp>



namespace engine::scene::components
{
	class movement: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "movement";



		movement() = default;

		void moveUp(float _delta_time) const noexcept;
		void moveRight(float _delta_time) const noexcept;
		void moveForward(float _delta_time) const noexcept;

		void moveWorldUp(float _delta_time) const noexcept;
		void moveWorldRight(float _delta_time) const noexcept;
		void moveWorldForward(float _delta_time) const noexcept;

		serialized_view_t serialize() const noexcept override;

	};
}