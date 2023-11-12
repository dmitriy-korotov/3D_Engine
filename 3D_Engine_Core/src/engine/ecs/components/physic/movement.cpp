#include <engine/ecs/components/physic/movement.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/orientation.hpp>

#include <engine/scene/world_data.hpp>



namespace engine::ecs::components
{
	void movement::moveUp(float _delta_time) const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = ECS::instance().getComponentsManager()->getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + orientation_comp->getUp() * _delta_time);
	}



	void movement::moveRight(float _delta_time) const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = ECS::instance().getComponentsManager()->getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + orientation_comp->getRight() * _delta_time);
	}



	void movement::moveForward(float _delta_time) const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = ECS::instance().getComponentsManager()->getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + orientation_comp->getForward() * _delta_time);
	}





	void movement::moveWorldUp(float _delta_time) const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = ECS::instance().getComponentsManager()->getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + scene::g_world_up_direction * _delta_time);
	}



	void movement::moveWorldRight(float _delta_time) const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = ECS::instance().getComponentsManager()->getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + scene::g_world_right_direction * _delta_time);
	}



	void movement::moveWorldForward(float _delta_time) const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = ECS::instance().getComponentsManager()->getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + scene::g_world_forward_direction * _delta_time);
	}
}