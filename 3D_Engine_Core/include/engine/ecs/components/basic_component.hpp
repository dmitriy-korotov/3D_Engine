#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/util/nocopyeble.hpp>



namespace engine::ecs::components
{
	template <typename T>
	class basic_component : private util::nocopyeble
	{
	public:

		static component_type_id s_component_type_id;

		basic_component() noexcept;

		entities::entity_id getOwner() const noexcept { return m_owner };
		component_id getID() const noexcept { return m_id; }

	private:

		static component_id generateComponentID() noexcept;

	private:

		static size_t m_components_count;

	private:

		entities::entity_id m_owner = entities::INVALID_ENTITY_ID;
		component_id m_id;

	};





	template <typename T>
	component_type_id basic_component<T>::s_component_type_id = typeid(T).get_hash();

	template <typename T>
	static size_t basic_component<T>::m_components_count = 0;



	template <typename T>
	basic_component<T>::basic_component() noexcept
			: m_id(generateComponentID())
	{ }



	template <typename T>
	component_id basic_component<T>::generateComponentID() noexcept
	{
		return ++m_components_count;
	}
}