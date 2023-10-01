#pragma once

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/util/nocopyeble.hpp>

#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include <typeinfo>



namespace engine::ecs::components
{
	class basic_component;

	class components_manager: private util::nocopyeble
	{
	public:

		template <typename T>
		using component_ptr = std::shared_ptr<T>;

		template <typename T>
		using component_iterator = typename std::unordered_map<entities::entity_id, component_ptr<T>>::iterator;

		template <typename T>
		using components_range = std::pair<component_iterator<T>, component_iterator<T>>;
		
		using general_type_components_map = std::unordered_map<entities::entity_id, component_ptr<basic_component>>;
		using components_storage = std::unordered_map<std::string_view, general_type_components_map>;

	public:

		template <typename ComponentType, typename ...Args>
		void addComponent(entities::entity_id _entity_id, Args&&... _args) noexcept;

		template <typename ComponentType>
		std::optional<components_range<ComponentType>> getComponents() const noexcept;

		template <typename ComponentType>
		component_ptr<ComponentType> getComponent(entities::entity_id _entity_id) const noexcept;

		template <typename ComponentType>
		void removeComponent(entities::entity_id _entity_id) noexcept;

		void removeAllComponents() noexcept;

	private:

		components_storage m_components;

	};





	template <typename ComponentType, typename ...Args>
	void components_manager::addComponent(entities::entity_id _entity_id, Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = std::make_shared<ComponentType>(std::forward<Args>(_args)...);
		component->setOwner(_entity_id);
		
		auto current_type_components = m_components.find(ComponentType::component_name);
		if (current_type_components == m_components.end())
		{
			general_type_components_map current_type_components_storage;
			ECS::instance().getEntitiesManager()->getEntity(_entity_id)->addComponent<ComponentType>(std::weak_ptr(component));
			current_type_components_storage.emplace(_entity_id, std::move(component));
			m_components.emplace(ComponentType::component_name, std::move(current_type_components_storage));
		}
		else
		{
			ECS::instance().getEntitiesManager()->getEntity(_entity_id)->addComponent<ComponentType>(std::weak_ptr(component));
			m_components.find(ComponentType::component_name)->second.emplace(_entity_id, std::move(component));
		}
	}



	template <typename ComponentType>
	void components_manager::removeComponent(entities::entity_id _entity_id) noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			components_range->erase(_entity_id);
		}
	}



	template <typename ComponentType>
	std::optional<components_manager::components_range<ComponentType>>
	components_manager::getComponents() const noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			auto range_begin = components_range->second.begin();
			auto range_end = components_range->second.end();
			return std::make_pair(*reinterpret_cast<components_manager::component_iterator<ComponentType>*>(&range_begin),
								  *reinterpret_cast<components_manager::component_iterator<ComponentType>*>(&range_end));
		}
		else
		{
			return std::nullopt;
		}
	}



	template <typename ComponentType>
	components_manager::component_ptr<ComponentType> 
	components_manager::getComponent(entities::entity_id _entity_id) const noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			auto component_iter = components_range->find(_entity_id);

			return component_iter == components_range.end() ? nullptr : component_iter->second;
		}
		else
		{
			return nullptr;
		}
	}
}