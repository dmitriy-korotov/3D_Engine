#include <engine/scene/components/physic/rotate.hpp>

#include <engine/logging/log.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/physic/rotation.hpp>



namespace engine::scene::components
{
	auto rotate::rotateX(float _delta_angle) const noexcept -> void
	{
		auto rotation_comp = Scene::getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_ERROR("[Rotate component ERROR] Entity hasn't 'rotation' component");
			return;
		}
		rotation_comp->setRotation(rotation_comp->getRotation() + glm::vec3(_delta_angle, 0.f, 0.f));
	}



	auto rotate::rotateY(float _delta_angle) const noexcept -> void
	{
		auto rotation_comp = Scene::getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_ERROR("[Rotate component ERROR] Entity hasn't 'rotation' component");
			return;
		}
		rotation_comp->setRotation(rotation_comp->getRotation() + glm::vec3(0.f, _delta_angle, 0.f));
	}



	auto rotate::rotateZ(float _delta_angle) const noexcept -> void
	{
		auto rotation_comp = Scene::getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_ERROR("[Rotate component ERROR] Entity hasn't 'rotation' component");
			return;
		}
		rotation_comp->setRotation(rotation_comp->getRotation() + glm::vec3(0.f, 0.f, _delta_angle));
	}



	auto rotate::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}