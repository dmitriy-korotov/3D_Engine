#pragma once

#include <engine/scene/Scene.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>



namespace engine::scene::systems
{
	class scene_UI final: public scene_system
	{
	public:

		static constexpr std::string_view system_name = "scene_UI";



		void update(float _delta_time) noexcept;
		void postUpdate(float _delta_time) noexcept;

		serialized_view_t serialize() const override;

	private:

		glm::vec4 m_bacgroud_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
		glm::vec3 m_light_direction = glm::vec3(0.f, 0.f, 0.f);

	};
}