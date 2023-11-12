#include <engine/ecs/components/physic/transform.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/scale.hpp>



namespace engine::ecs::components
{
	glm::mat4 transform::getModelMatrix() const noexcept
	{
		const auto& owner = ECS::instance().getEntitiesManager()->getEntity(getOwner());

		auto position_comp = owner->getComponent<position>();
		auto rotation_comp = owner->getComponent<rotation>();
		auto scale_comp	   = owner->getComponent<scale>();

		glm::mat4 translate_matrix =	position_comp != nullptr ? position_comp->getTranslateMatrix()	: glm::mat4(1.f);
		glm::mat4 rotation_matrix =		rotation_comp != nullptr ? rotation_comp->getRotationMatrix()	: glm::mat4(1.f);
		glm::mat4 scale_matrix =		scale_comp != nullptr	 ? scale_comp->getScaleMatrix()			: glm::mat4(1.f);

		return translate_matrix * rotation_matrix * scale_matrix;
	}



	glm::mat3 transform::getNormalMatrix() const noexcept
	{
		return glm::mat3(glm::transpose(glm::inverse(getModelMatrix())));
	}
}