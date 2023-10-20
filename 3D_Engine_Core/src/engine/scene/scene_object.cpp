#include <engine/scene/scene_object.hpp>

#include <engine/ecs/components/physic/position.hpp>





using namespace engine::ecs::components;

namespace engine::scene
{
	scene_object::scene_object(const glm::vec3& _position) noexcept
	{
		addComponent<position>(_position);
	}
}