#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/components/basic_component.hpp>

#include <unordered_map>
#include <concepts>
#include <memory>



namespace engine::ecs::entities
{
	class basic_entity: private util::nocopyeble
	{
	public:

		basic_entity() noexcept;
		virtual ~basic_entity();

		entity_id_t getID() const noexcept;

	protected:

		static entity_id_t generateEntityId() noexcept;
		static entity_id_t m_next_entity_id;

	protected:

		entity_id_t m_id = INVALID_ENTITY_ID;

	};



	template <typename T>
	concept Entity = std::derived_from<T, basic_entity> || std::is_same_v<T, basic_entity>;
}