#pragma once

#include <engine/ecs/entities/basic_entity.hpp>

#include <glm/vec3.hpp>



namespace engine::scene
{
	class scene_object: public virtual ecs::entities::basic_entity
	{
	public:

		scene_object(const glm::vec3& _position = glm::vec3(0.f)) noexcept;

	};
}