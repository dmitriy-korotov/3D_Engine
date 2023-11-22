#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/scene/objects/fwd/scene_object.hpp>
#include <engine/scene/components/fwd/scene_component.hpp>
#include <engine/scene/systems/fwd/scene_system.hpp>



namespace engine::scene
{
	using object_id_t = ecs::entities::entity_id_t;
	using component_id_t = ecs::components::component_id_t;
	using system_id_t = ecs::systems::system_id_t;

	using basic_object_t = objects::scene_object;
	using basic_component_t = components::scene_component;
	using basic_system_t = systems::scene_system;
}