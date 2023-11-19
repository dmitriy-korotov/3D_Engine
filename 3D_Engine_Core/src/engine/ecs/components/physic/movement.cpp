#include <engine/ecs/components/physic/movement.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/orientation.hpp>

#include <engine/scene/world_data.hpp>



namespace engine::ecs::components
{
	void movement::moveUp(float _delta_time) const noexcept
	{
		auto position_comp = scene::Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = scene::Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + orientation_comp->getUp() * _delta_time);
	}



	void movement::moveRight(float _delta_time) const noexcept
	{
		auto position_comp = scene::Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = scene::Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + orientation_comp->getRight() * _delta_time);
	}



	void movement::moveForward(float _delta_time) const noexcept
	{
		auto position_comp = scene::Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = scene::Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + orientation_comp->getForward() * _delta_time);
	}





	void movement::moveWorldUp(float _delta_time) const noexcept
	{
		auto position_comp = scene::Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = scene::Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + scene::g_world_up_direction * _delta_time);
	}



	void movement::moveWorldRight(float _delta_time) const noexcept
	{
		auto position_comp = scene::Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = scene::Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + scene::g_world_right_direction * _delta_time);
	}



	void movement::moveWorldForward(float _delta_time) const noexcept
	{
		auto position_comp = scene::Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
			return;

		auto orientation_comp = scene::Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
			return;

		position_comp->setPosition(position_comp->getPosition() + scene::g_world_forward_direction * _delta_time);
	}



	auto movement::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}