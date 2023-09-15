#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/util/nocopyeble.hpp>

#include <unordered_map>
#include <vector>
#include <memory>



namespace engine::ecs::components
{
	class basic_component;

	class components_manager : private util::nocopyeble
	{
	public:

		using component_ptr = std::shared_ptr<basic_component>;
		using components_storage = std::unordered_map<component_type_id, std::vector<component_ptr>>;

		template <typename ComponentType, typename ...Args>
		void addComponent(entities::entity_id _entity_id, Args&&... _args) noexcept;

		void removeAllComponents() noexcept;

	private:

		components_storage m_components;

	};





	template <typename ComponentType, typename ...Args>
	void components_manager::addComponent(entities::entity_id _entity_id, Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v <basic_component, ComponentType> "ComponentType is not derived basic_component");

		ComponentType component = ComponentType(std::forward<Args>(_args)...);
		component.setOwner(_entity_id);
		m_components.emplace(ComponentType::s_component_type_id, component);
	}
}