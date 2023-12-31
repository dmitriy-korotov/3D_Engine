#include <engine/scene/components/physic/camera_transform.hpp>

#include <engine/logging/log.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/physic/position.hpp>
#include <engine/scene/components/physic/rotation.hpp>
#include <engine/scene/components/physic/orientation.hpp>

#include <engine/scene/world_data.hpp>

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>



namespace engine::scene::components
{
	auto camera_transform::getViewMatrix() const noexcept -> glm::mat4
	{
		auto position_comp =	Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
		{
			LOG_WARN("[Camera transform WARN] Entity hasn't position component");
			return glm::mat4(1.f);
		}
		auto rotation_comp =	Scene::getComponent<rotation>(getOwner());
		if (rotation_comp == nullptr)
		{
			LOG_WARN("[Camera transform WARN] Entity hasn't rotation component");
			return glm::mat4(1.f);
		}
		auto orientation_comp = Scene::getComponent<orientation>(getOwner());
		if (orientation_comp == nullptr)
		{
			LOG_WARN("[Camera transform WARN] Entity hasn't orientation component");
			return glm::mat4(1.f);
		}


		float roll_in_radians =		-glm::radians(rotation_comp->getRotation().x);
		float pitch_in_radians =	-glm::radians(rotation_comp->getRotation().y);
		float yaw_in_radians =		-glm::radians(rotation_comp->getRotation().z);

		glm::mat3 rotate_matrix_x(1.f,		0.f,					0.f,
								  0.f,		cos(roll_in_radians),	sin(roll_in_radians),
								  0.f,		-sin(roll_in_radians),	cos(roll_in_radians));

		glm::mat3 rotate_matrix_y(cos(pitch_in_radians),	 0.f,		-sin(pitch_in_radians),
								  0.f,						 1.f,		0.f,
								  sin(pitch_in_radians),	 0.f,		cos(pitch_in_radians));

		glm::mat3 rotate_matrix_z(glm::cos(yaw_in_radians),			glm::sin(yaw_in_radians),	0.f,
								  -glm::sin(yaw_in_radians),		glm::cos(yaw_in_radians),	0.f,
								  0.f,								0.f,						1.f);

		glm::mat3 euler_rotate_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x;



		glm::vec3 forward = euler_rotate_matrix * scene::g_world_forward_direction;
		glm::vec3 right =	euler_rotate_matrix * scene::g_world_right_direction;

		orientation_comp->setOrientation(forward, right);

		return glm::lookAt(position_comp->getPosition(), position_comp->getPosition() + orientation_comp->getForward(), orientation_comp->getUp());
	}



	auto camera_transform::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}