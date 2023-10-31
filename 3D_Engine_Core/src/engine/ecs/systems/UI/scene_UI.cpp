#include <engine/ecs/systems/UI/scene_UI.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/Engine.hpp>

#include <engine/ecs/components/render/light/direction_light.hpp>





using namespace engine::ecs::components;
using namespace engine::scene;

namespace engine::ecs::systems
{
	void scene_UI::update([[maybe_unused]] float _delta_time) const noexcept
	{
		auto component = Scene::getComponent<direction_light>();
		if (component == nullptr)
			return;



		auto& UI_module = Engine::getApplicationUIModule();



		UI_module->createDockSpace();
		


		UI_module->begin("Scene");

		UI_module->putColorEdit4("Background color", m_bacgroud_color);

		UI_module->separate();

		component->putOnUI();

		UI_module->end();
	}



	void scene_UI::postUpdate([[maybe_unused]] float _delta_time) const noexcept
	{
		Engine::getApplicationRenderer()->setClearColor(m_bacgroud_color.r, m_bacgroud_color.g, m_bacgroud_color.b, m_bacgroud_color.a);
	}





	json scene_UI::dump() const
	{
		json serialized_view = basic_system::dump();

		serialized_view["system_name"] = system_name;

		return serialized_view;
	}
}