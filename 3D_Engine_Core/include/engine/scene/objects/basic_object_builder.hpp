#pragma once

#include <engine/scene/common_types.hpp>



namespace engine::scene
{
	class basic_object_builder
	{
	public:

		virtual ~basic_object_builder() = default;

		virtual void build(object_id_t _obj_id) const noexcept = 0;

	};
}