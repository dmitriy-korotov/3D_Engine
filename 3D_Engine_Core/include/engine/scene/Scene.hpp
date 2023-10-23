#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/scene/common_types.hpp>

#include <engine/scene/objects/fwd/basic_object_builder.hpp>

#include <memory>



namespace engine::scene
{
	class Scene: private util::noconstructible
	{
	public:

		using object_builder_ptr_t = std::shared_ptr<basic_object_builder>;



		/*template <typename T>
		static object_id_t addObject(const object_builder_ptr_t& _obj_builder = nullptr) noexcept;

		static bool delObject(object_id_t _obj_id) noexcept;

		template <typename T>
		static bool addComponent(object_id_t _obj_id) noexcept;

		template <typename T>
		static bool getComponent(object_id_t _obj_id) noexcept;*/

	};
}