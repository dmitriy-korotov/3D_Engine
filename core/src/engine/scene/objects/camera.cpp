#include <engine/scene/objects/camera.hpp>

#include <engine/scene/components/physic.hpp>
#include <engine/scene/components/render.hpp>



namespace engine::scene::objects
{
	camera::camera(const glm::vec3& _position, Projection _projection_mode) noexcept
			: scene_object(_position)
	{
		using namespace components;

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