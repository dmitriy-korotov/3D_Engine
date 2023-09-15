#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/util/nocopyeble.hpp>



namespace engine::ecs::entities
{
	class entity_manager;

	class basic_entity : private util::nocopyeble
	{
	public:

		friend entity_manager;

		basic_entity();
		virtual ~basic_entity();

		entity_id getEntityId() const noexcept;

	private:

		static entity_id generateEntityId() noexcept;

		static entity_id m_entities_count;

	private:

		entity_id m_id;

	};
}