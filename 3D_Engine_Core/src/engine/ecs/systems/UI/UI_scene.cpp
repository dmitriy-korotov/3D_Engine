#include <engine/ecs/systems/UI/UI_scene.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/render/open_gl/renderer_open_gl.hpp>

#include <engine/modules/imgui/UIModule.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/render/light/direction_light.hpp>

#include <imgui/imgui.h>



using namespace engine::modules::imgui;

namespace engine::ecs::systems
{
	void UI_scene::update(float _delta_time) const noexcept
	{
		auto components = ECS::instance().getComponentsManager()->getComponents<components::direction_light>();
		if (components.has_value())
		{
			glm::vec3 direction = components->first->getDirection();
			m_light_direction[0] = direction.x;
			m_light_direction[1] = direction.y;
			m_light_direction[2] = direction.z;
		}

		UIModule::instance().onUIDrawBegin();

		UIModule::instance().createDockSpace();

		ImGui::Begin("Scene");

		ImGui::ColorEdit4("Bacground color", m_bacgroud_color.data());
		ImGui::Separator();
		ImGui::SliderFloat3("Scene light direction", m_light_direction.data(), -1.f, 1.f);

		ImGui::End();
		

		UIModule::instance().onUIDrawEnd();

		if (components.has_value())
		{
			glm::vec3 direction = glm::vec3(m_light_direction[0], m_light_direction[1], m_light_direction[2]);
			components->first->setDirection(direction);
		}

		render::open_gl::renderer::instance().setClearColor(m_bacgroud_color[0], m_bacgroud_color[1], m_bacgroud_color[2], m_bacgroud_color[3]);
	}
}