#include <engine/ecs/systems/UI/selected_object_UI.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/ecs/components/markers.hpp>
#include <engine/ecs/components/physic.hpp>
#include <engine/ecs/components/render.hpp>

#include <engine/Engine.hpp>





using namespace engine::ecs::components;
using namespace engine::scene;

namespace engine::ecs::systems
{
	selected_object_UI::selected_object_UI() noexcept
			: m_UI_module(Engine::getApplicationUIModule())
	{ }



	void selected_object_UI::preUpdate(float _delta_time) const noexcept
	{
		m_UI_module.get()->begin("Selected object");
	}



	void selected_object_UI::update(float _delta_time) const noexcept
	{
		auto selected_component = Scene::getComponent<selected>();
		if (selected_component == nullptr)
			return;

		auto& owner = Scene::getObject(selected_component->getOwner());



		auto& position_comp = owner->getComponent<position>();
		if (position_comp != nullptr)
			position_comp->putOnUI();

		auto& rotation_comp = owner->getComponent<rotation>();
		if (rotation_comp != nullptr)
			rotation_comp->putOnUI();

		auto& scale_comp = owner->getComponent<scale>();
		if (scale_comp != nullptr)
			scale_comp->putOnUI();

		auto& point_light_comp = owner->getComponent<point_light>();
		if (point_light_comp != nullptr)
			point_light_comp->putOnUI();

		m_UI_module->separate();

		auto& renderable_comp = owner->getComponent<renderable>();
		if (renderable_comp != nullptr)
			renderable_comp->putOnUI();
	}



	void selected_object_UI::postUpdate(float _delta_time) const noexcept
	{
		m_UI_module.get()->end();
	}





	json selected_object_UI::dump() const
	{
		json serialized_view = basic_system::dump();

		serialized_view["system_name"] = system_name;

		return serialized_view;
	}
}