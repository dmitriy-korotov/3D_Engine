#include <engine/scene/scene_object.hpp>

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/scale.hpp>



using namespace engine::ecs::components;

namespace engine::scene
{
	scene_object::scene_object() noexcept
	{
		addComponent<position>();
	}
}