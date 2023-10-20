#include <engine/scene/objects/camera.hpp>

#include <engine/ecs/components/physic.hpp>
#include <engine/ecs/components/render.hpp>





using namespace engine::ecs::components;

namespace engine::scene
{
	camera::camera(const glm::vec3& _position, Projection _projection_mode) noexcept
			: scene_object(_position)
	{
		addComponent<rotation>();
		addComponent<orientation>();
		addComponent<camera_transform>();
		
		addComponent<movement>();
		addComponent<movement_velocity>();
		addComponent<rotate>();
		addComponent<rotate_velocity>();

		addComponent<vision>(_projection_mode);
	}
}