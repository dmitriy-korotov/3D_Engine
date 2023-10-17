#include <engine/ecs/components/physic/rotate.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/physic/rotation.hpp>



namespace engine::ecs::components
{
	void rotate::rotateX(float _delta_angle) const noexcept
	{
		auto rotation_comp = ECS::instance().getComponentsManager()->getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_ERROR("[Rotate component ERROR] Entity hasn't 'rotation' component");
			return;
		}
		rotation_comp->setRotation(rotation_comp->getRotation() + glm::vec3(_delta_angle, 0.f, 0.f));
	}



	void rotate::rotateY(float _delta_angle) const noexcept
	{
		auto rotation_comp = ECS::instance().getComponentsManager()->getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_ERROR("[Rotate component ERROR] Entity hasn't 'rotation' component");
			return;
		}
		rotation_comp->setRotation(rotation_comp->getRotation() + glm::vec3(0.f, _delta_angle, 0.f));
	}



	void rotate::rotateZ(float _delta_angle) const noexcept
	{
		auto rotation_comp = ECS::instance().getComponentsManager()->getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_ERROR("[Rotate component ERROR] Entity hasn't 'rotation' component");
			return;
		}
		rotation_comp->setRotation(rotation_comp->getRotation() + glm::vec3(0.f, 0.f, _delta_angle));
	}
}