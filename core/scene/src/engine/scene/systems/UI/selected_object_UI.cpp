#include <engine/scene/systems/UI/selected_object_UI.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/markers.hpp>
#include <engine/scene/components/physic.hpp>
#include <engine/scene/components/render.hpp>

#include <engine/Engine.hpp>





using namespace engine::scene::components;

namespace engine::scene::systems
{
	selected_object_UI::selected_object_UI() noexcept
			: m_UI_module(Engine::getApplicationUIModule())
	{ }



	auto selected_object_UI::preUpdate(float _delta_time) noexcept -> void
	{
		m_UI_module.get()->begin("Selected object");
	}



	auto selected_object_UI::update(float _delta_time) noexcept -> void
	{
		auto selected_component = Scene::getComponent<selected>();
		if (selected_component == nullptr)
			return;

		const auto& owner = Scene::getObject(selected_component->getOwner());



		const auto& position_comp = owner->getComponent<position>();
		if (position_comp != nullptr)
			position_comp->putOnUI();

		const auto& rotation_comp = owner->getComponent<rotation>();
		if (rotation_comp != nullptr)
			rotation_comp->putOnUI();

		const auto& scale_comp = owner->getComponent<scale>();
		if (scale_comp != nullptr)
			scale_comp->putOnUI();

		const auto& point_light_comp = owner->getComponent<point_light>();
		if (point_light_comp != nullptr)
			point_light_comp->putOnUI();

		m_UI_module->separate();

		const auto& renderable_comp = owner->getComponent<renderable>();
		if (renderable_comp != nullptr)
			renderable_comp->putOnUI();
	}



	auto selected_object_UI::postUpdate(float _delta_time) noexcept -> void
	{
		m_UI_module.get()->end();
	}



	auto selected_object_UI::serialize() const -> serialized_view_t
	{
		serialized_view_t serialized_view = scene_system::serialize();

		serialized_view["system_name"] = system_name;

		return serialized_view;
	}
}