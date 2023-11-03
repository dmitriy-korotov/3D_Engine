#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/interfaces/serializable_object.hpp>

#include <engine/ecs/ecs.hpp>

#include <engine/ecs/components/fwd/components_manager.hpp>

#include <string>



namespace engine::ecs::components
{
	class basic_component: private util::nocopyeble, protected interfaces::serializable_object
	{
	public:

		friend components_manager;

		virtual ~basic_component() = default;

		virtual void onConstruct() noexcept;

		bool isActive() const noexcept;
		void enable() noexcept;
		void disable() noexcept;

		entities::entity_id_t getOwner() const noexcept;
		component_id_t getID() const noexcept;

		virtual bool putOnUI() noexcept;
		
		json dump() const override;
		void load(const json& _serialized_view) override;

	protected:

		basic_component() noexcept;

	private:

		void setOwner(entities::entity_id_t _entity_id) noexcept;
		
		static component_id_t generateComponentID() noexcept;

	private:

		static size_t m_next_component_id;

	private:

		bool m_is_active = true;
		entities::entity_id_t m_owner = entities::INVALID_ENTITY_ID;
		component_id_t m_id = INVALID_COMPONENT_ID;

	};
}