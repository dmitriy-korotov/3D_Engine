#include <engine/ecs/systems/UI/selected_object_UI.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/markers.hpp>
#include <engine/ecs/components/physic.hpp>
#include <engine/ecs/components/render.hpp>

#include <engine/Engine.hpp>





using namespace engine::ecs::components;

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
		auto selected_component = ECS::instance().getComponentsManager()->getComponent<selected>();
		if (selected_component == nullptr)
			return;

		auto& owner = ECS::instance().getEntitiesManager()->getEntity(selected_component->getOwner());



		auto& position_opt = owner->getComponent<position>();
		if (position_opt.has_value())
			position_opt->lock()->putOnUI();

		auto& rotation_opt = owner->getComponent<rotation>();
		if (rotation_opt.has_value())
			rotation_opt->lock()->putOnUI();

		auto& scale_opt = owner->getComponent<scale>();
		if (scale_opt.has_value())
			scale_opt->lock()->putOnUI();

		m_UI_module->separate();

		auto& renderable_opt = owner->getComponent<renderable>();
		if (renderable_opt.has_value())
			renderable_opt->lock()->putOnUI();
	}



	void selected_object_UI::postUpdate(float _delta_time) const noexcept
	{
		m_UI_module.get()->end();
	}
}