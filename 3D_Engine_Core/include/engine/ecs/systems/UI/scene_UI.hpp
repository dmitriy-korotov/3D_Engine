#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>



namespace engine::ecs::systems
{
	class scene_UI: public basic_system
	{
	public:

		static constexpr std::string_view system_name = "scene_UI";

		void update(float _delta_time) const noexcept;
		void postUpdate(float _delta_time) const noexcept;

		serialized_view_t serialize() const override;

	private:

		mutable glm::vec4 m_bacgroud_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
		mutable glm::vec3 m_light_direction = glm::vec3(0.f, 0.f, 0.f);

	};
}