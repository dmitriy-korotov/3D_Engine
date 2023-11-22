#pragma once

#include <engine/scene/Scene.hpp>

#include <glm/vec3.hpp>



namespace engine::scene::components
{
	class direction: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "direction";



		direction(const glm::vec3& _direction = glm::vec3(0.f, 0.f, -1.f)) noexcept;

		void setDirection(const glm::vec3& _direction) noexcept;

		const glm::vec3& getDirection() const noexcept;

		bool putOnUI() noexcept;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	protected:

		glm::vec3 m_direction;

	};
}