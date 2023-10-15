#include <engine/ecs/systems/UI/scene_UI.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/Engine.hpp>

#include <engine/ecs/components/render/light/direction_light.hpp>



namespace engine::ecs::systems
{
	void scene_UI::update([[maybe_unused]] float _delta_time) const noexcept
	{
		auto components = ECS::instance().getComponentsManager()->getComponents<components::direction_light>();
		if (components.has_value())
			m_light_direction = components->first->getDirection();



		auto& UI_module = Engine::getApplicationUIModule();



		UI_module->createDockSpace();
		


		UI_module->begin("Scene");

		UI_module->putColorEdit4("Bacground color", m_bacgroud_color);
		UI_module->separate();
		UI_module->putSliderFloat3("Scene light direction", m_light_direction, -1.f, 1.f);

		UI_module->end();
		


		if (components.has_value())
			components->first->setDirection(m_light_direction);
	}



	void scene_UI::postUpdate([[maybe_unused]] float _delta_time) const noexcept
	{
		Engine::getApplicationRenderer()->setClearColor(m_bacgroud_color.r, m_bacgroud_color.g, m_bacgroud_color.b, m_bacgroud_color.a);
	}
}