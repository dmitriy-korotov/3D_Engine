#include <engine/ecs/components/physic/transform.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/physic/position.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/scale.hpp>



namespace engine::ecs::components
{
	glm::mat4 transform::getModelMatrix() const noexcept
	{
		const auto& owner = ECS::instance().getEntitiesManager()->getEntity(getOwner());

		auto position_opt = owner->getComponent<position>();
		auto rotation_opt = owner->getComponent<rotation>();
		auto scale_opt =	owner->getComponent<scale>();

		glm::mat4 translate_matrix =	position_opt.has_value() ? position_opt->lock()->getTranslateMatrix() : glm::mat4(1.f);
		glm::mat4 rotation_matrix =		rotation_opt.has_value() ? rotation_opt->lock()->getRotationMatrix() : glm::mat4(1.f);
		glm::mat4 scale_matrix =		scale_opt.has_value() ? scale_opt->lock()->getScaleMatrix() : glm::mat4(1.f);

		return translate_matrix * rotation_matrix * scale_matrix;
	}



	glm::mat3 transform::getNormalMatrix() const noexcept
	{
		return glm::mat3(glm::transpose(glm::inverse(getModelMatrix())));
	}
}