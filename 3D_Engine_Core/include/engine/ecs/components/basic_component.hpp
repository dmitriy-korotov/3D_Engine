#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/util/nocopyeble.hpp>

#include <string>



namespace engine::ecs::components
{
	class components_manager;

	class basic_component: private util::nocopyeble
	{
	public:

		friend components_manager;

		basic_component() noexcept;
		virtual ~basic_component() = default;

		bool isActive() const noexcept;
		void enable() noexcept;
		void disable() noexcept;

		entities::entity_id getOwner() const noexcept;
		component_id getID() const noexcept;

		virtual bool putOnUI() noexcept;

	private:

		void setOwner(entities::entity_id _entity_id) noexcept;
		
		static component_id generateComponentID() noexcept;

	private:

		static size_t m_next_component_id;

	private:

		bool m_is_active = true;
		entities::entity_id m_owner = entities::INVALID_ENTITY_ID;
		component_id m_id = INVALID_COMPONENT_ID;

	};
}