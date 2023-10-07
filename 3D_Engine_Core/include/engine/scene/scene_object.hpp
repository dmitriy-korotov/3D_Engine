#pragma once

#include <engine/ecs/entities/basic_entity.hpp>



namespace engine::scene
{
	class scene_object : public virtual ecs::entities::basic_entity
	{
	public:

		scene_object() noexcept;

	};
}