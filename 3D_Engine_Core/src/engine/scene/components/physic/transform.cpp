#include <engine/scene/components/physic/transform.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/physic/position.hpp>
#include <engine/scene/components/physic/rotation.hpp>
#include <engine/scene/components/physic/scale.hpp>



namespace engine::scene::components
{
	auto transform::getModelMatrix() const noexcept -> glm::mat4
	{
		const auto& owner = Scene::getObject(getOwner());

		auto position_comp = owner->getComponent<position>();
		auto rotation_comp = owner->getComponent<rotation>();
		auto scale_comp	   = owner->getComponent<scale>();

		glm::mat4 translate_matrix =	position_comp != nullptr ? position_comp->getTranslateMatrix()	: glm::mat4(1.f);
		glm::mat4 rotation_matrix =		rotation_comp != nullptr ? rotation_comp->getRotationMatrix()	: glm::mat4(1.f);
		glm::mat4 scale_matrix =		scale_comp != nullptr	 ? scale_comp->getScaleMatrix()			: glm::mat4(1.f);

		return translate_matrix * rotation_matrix * scale_matrix;
	}



	auto transform::getNormalMatrix() const noexcept -> glm::mat3
	{
		return glm::mat3(glm::transpose(glm::inverse(getModelMatrix())));
	}



	auto transform::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}