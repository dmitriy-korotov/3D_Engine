#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/util/nocopyeble.hpp>



namespace engine::ecs::components
{
	class components_manager;

	class basic_component : private util::nocopyeble
	{
	public:

		friend components_manager;

		basic_component() noexcept;

		entities::entity_id getOwner() const noexcept { return m_owner; };
		component_id getID() const noexcept { return m_id; }

	private:

		void setOwner(entities::entity_id _entity_id) noexcept;

		static void setComponentTypeID(component_type_id _component_type_id) noexcept;
		static component_type_id getComponentTypeID() noexcept;
		static component_id generateComponentID() noexcept;

	private:

		static size_t m_components_count;
		static component_type_id s_component_type_id;

	private:

		entities::entity_id m_owner = entities::INVALID_ENTITY_ID;
		component_id m_id = INVALID_COMPONENT_ID;

	};
}