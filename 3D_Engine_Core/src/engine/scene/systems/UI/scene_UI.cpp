#include <engine/scene/systems/UI/scene_UI.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/Engine.hpp>

#include <engine/scene/components/render/light/direction_light.hpp>





using namespace engine::scene::components;

namespace engine::scene::systems
{
	auto scene_UI::update([[maybe_unused]] float _delta_time) const noexcept -> void
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



	auto scene_UI::postUpdate([[maybe_unused]] float _delta_time) const noexcept -> void
	{
		Engine::getApplicationRenderer()->setClearColor(m_bacgroud_color.r, m_bacgroud_color.g, m_bacgroud_color.b, m_bacgroud_color.a);
	}



	auto scene_UI::serialize() const -> serialized_view_t
	{
		serialized_view_t serialized_view = scene_system::serialize();

		serialized_view["system_name"] = system_name;

		return serialized_view;
	}
}