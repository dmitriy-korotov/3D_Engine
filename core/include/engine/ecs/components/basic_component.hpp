#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/interfaces/serializable_object.hpp>

#include <engine/ecs/ecs.hpp>

#include <string>
#include <concepts>



namespace engine::ecs::components
{
	class basic_component: private util::nocopyeble
	{
	public:

		virtual ~basic_component() = default;

		virtual void onConstruct() noexcept;

		bool isActive() const noexcept;
		void enable() noexcept;
		void disable() noexcept;

		void setOwner(entities::entity_id_t _entity_id) noexcept;
		entities::entity_id_t getOwner() const noexcept;
		component_id_t getID() const noexcept;

		virtual bool putOnUI() noexcept;

	protected:

		basic_component() noexcept;

		void setID(component_id_t _id) noexcept;

	private:
		
		static component_id_t generateComponentID() noexcept;

	private:

		static size_t m_next_component_id;

	private:

		bool m_is_active = true;
		entities::entity_id_t m_owner = entities::INVALID_ENTITY_ID;
		component_id_t m_id = INVALID_COMPONENT_ID;

	};



	template <typename T>
	concept Component = (std::is_same_v<T, basic_component> || std::derived_from<T, basic_component>) && requires {
		{ T::component_name } -> std::convertible_to<std::string_view>;
	};
}