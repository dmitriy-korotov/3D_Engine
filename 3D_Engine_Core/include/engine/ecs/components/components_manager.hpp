#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/ecs/components/component_iterator.hpp>

#include <engine/ecs/components/fwd/basic_component.hpp>

#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>



namespace engine::ecs::components
{
	class components_manager: private util::nocopyeble
	{
	public:

		friend entities::basic_entity;

		template <typename T>
		using component_ptr_t = std::shared_ptr<T>;

		template <typename T>
		using components_range_t = std::pair<component_iterator<T>, component_iterator<T>>;
		
		template <typename T>
		using components_map_t = std::unordered_map<entities::entity_id_t, component_ptr_t<T>>;

		using general_type_components_map_t = components_map_t<basic_component>;
		using components_storage_t = std::unordered_map<std::string_view, general_type_components_map_t>;

	public:

		template <typename ComponentType, typename ...Args>
		bool addComponent(entities::entity_id_t _entity_id, Args&&... _args) noexcept;

		template <typename ComponentType>
		std::optional<components_range_t<ComponentType>> getComponents() const noexcept;

		template <typename ComponentType>
		component_ptr_t<ComponentType> getComponent() const noexcept;

		template <typename ComponentType>
		component_ptr_t<ComponentType> getComponent(entities::entity_id_t _entity_id) const noexcept;

		template <typename ComponentType>
		bool hasComponent(entities::entity_id_t _entity_id) const noexcept;

		template <typename ComponentType>
		void removeComponent(entities::entity_id_t _entity_id) noexcept;

		void removeAllComponents() noexcept;

	private:

		template <typename ComponentType, typename ...Args>
		component_ptr_t<ComponentType> addComponentNotConstructedEntity(entities::entity_id_t _entity_id, Args&&... _args) noexcept;

	private:

		components_storage_t m_components;

	};





	template <typename ComponentType, typename ...Args>
	bool components_manager::addComponent(entities::entity_id_t _entity_id, Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = std::make_shared<ComponentType>(std::forward<Args>(_args)...);
		component->setOwner(_entity_id);
		component->onConstruct();
		
		auto current_type_components = m_components.find(ComponentType::component_name);
		if (current_type_components == m_components.end())
		{
			general_type_components_map_t current_type_components_storage;
			auto& entity = ECS::instance().getEntitiesManager()->getEntity(_entity_id);
			if (entity != nullptr)
			{
				entity->addComponent<ComponentType>(std::weak_ptr(component));
			}
			else
			{
				LOG_ERROR("[Components manager ERROR] Can't find entity (entity_id: {0})", _entity_id);
				return false;
			}
			current_type_components_storage.emplace(_entity_id, std::move(component));
			m_components.emplace(ComponentType::component_name, std::move(current_type_components_storage));
		}
		else
		{
			ECS::instance().getEntitiesManager()->getEntity(_entity_id)->addComponent<ComponentType>(std::weak_ptr(component));
			m_components.find(ComponentType::component_name)->second.emplace(_entity_id, std::move(component));
		}
		return true;
	}



	template <typename ComponentType, typename ...Args>
	components_manager::component_ptr_t<ComponentType>
	components_manager::addComponentNotConstructedEntity(entities::entity_id_t _entity_id, Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = std::make_shared<ComponentType>(std::forward<Args>(_args)...);
		component->setOwner(_entity_id);
		component->onConstruct();

		auto current_type_components = m_components.find(ComponentType::component_name);
		if (current_type_components == m_components.end())
		{
			general_type_components_map_t current_type_components_storage;
			current_type_components_storage.emplace(_entity_id, component);
			m_components.emplace(ComponentType::component_name, std::move(current_type_components_storage));
		}
		else
		{
			m_components.find(ComponentType::component_name)->second.emplace(_entity_id, component);
		}
		return component;
	}



	template <typename ComponentType>
	void components_manager::removeComponent(entities::entity_id_t _entity_id) noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
			components_range->second.erase(_entity_id);
	}



	template <typename ComponentType>
	std::optional<components_manager::components_range_t<ComponentType>>
	components_manager::getComponents() const noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			auto range_begin = components_range->second.begin();
			auto range_end = components_range->second.end();

			return std::make_pair(component_iterator<ComponentType>(std::move(range_begin)), component_iterator<ComponentType>(std::move(range_end)));
		}
		else
		{
			return std::nullopt;
		}
	}



	template <typename ComponentType>
	components_manager::component_ptr_t<ComponentType>
	components_manager::getComponent() const noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			auto& components = components_range->second;

			if (components.size() > 1)
				LOG_WARN("[Components manager WARN] Components '{0}' more then one, returned first", ComponentType::component_name);

			if (components.size() == 1)
				return std::dynamic_pointer_cast<ComponentType>(components.begin()->second);
		}
		return nullptr;
	}



	template <typename ComponentType>
	components_manager::component_ptr_t<ComponentType> 
	components_manager::getComponent(entities::entity_id_t _entity_id) const noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			auto component_iter = components_range->second.find(_entity_id);

			if (component_iter != components_range->second.end())
				return std::dynamic_pointer_cast<ComponentType>(component_iter->second);
		}
		return nullptr;
	}



	template <typename ComponentType>
	bool components_manager::hasComponent(entities::entity_id_t _entity_id) const noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::component_name);
		if (components_range != m_components.end())
		{
			auto component_iter = components_range->second.find(_entity_id);

			return (component_iter != components_range->second.end());
		}
		return false;
	}
}