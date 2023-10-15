#include <engine/ecs/systems/UI/selected_object_UI.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/markers.hpp>
#include <engine/ecs/components/physic.hpp>

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


		

		auto& transform_opt = owner->getComponent<transform>();
		if (transform_opt.has_value())
			transform_opt->lock()->putOnUI();

	}



	void selected_object_UI::postUpdate(float _delta_time) const noexcept
	{
		m_UI_module.get()->end();
	}
}