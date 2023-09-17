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

	class components_manager : private util::nocopyeble
	{
	public:

		template <typename T>
		using component_iterator = typename std::vector<std::shared_ptr<T>>::iterator;

		template <typename T>
		using components_range = std::pair<component_iterator<T>, component_iterator<T>>;
		
		template <typename T>
		using component_ptr = std::shared_ptr<T>;
		
		using components_storage = std::unordered_map<component_type_id, std::vector<component_ptr<basic_component>>>;

	public:

		template <typename ComponentType, typename ...Args>
		void addComponent(entities::entity_id _entity_id, Args&&... _args) noexcept;

		template <typename ComponentType>
		std::optional<components_range<ComponentType>> getComponents() noexcept;

		template <typename ComponentType>
		component_ptr<ComponentType> getComponent(entities::entity_id _entity_id) noexcept;

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
		if (ComponentType::getComponentTypeID() == INVALID_COMPONENT_TYPE_ID)
		{
			ComponentType::setComponentTypeID(typeid(ComponentType).hash_code());
			std::vector<component_ptr<basic_component>> this_type_components_storage;
			ECS::getEntitiesManager()->getEntity(_entity_id)->addComponent<ComponentType>(std::weak_ptr(component));
			this_type_components_storage.push_back(std::move(component));
			m_components.emplace(ComponentType::getComponentTypeID(), std::move(this_type_components_storage));
		}
		else
		{
			ECS::getEntitiesManager()->getEntity(_entity_id)->addComponent<ComponentType>(std::weak_ptr(component));
			m_components.find(ComponentType::getComponentTypeID())->second.push_back(std::move(component));
		}
	}



	template <typename ComponentType>
	std::optional<components_manager::components_range<ComponentType>>
	components_manager::getComponents() noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::getComponentTypeID());
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
	components_manager::getComponent(entities::entity_id _entity_id) noexcept
	{
		static_assert(std::is_base_of_v<basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto components_range = m_components.find(ComponentType::getComponentTypeID());
		if (components_range != m_components.end())
		{
			auto component_iter = std::find(
				[&_entity_id](const auto& component_ptr) -> bool
				{
					return component_ptr->getOwner() == _entity_id;
				}, components_range->second.begin(), components_range->second.end());

			return component_iter == m_components.end() ? nullptr : *component_iter;
		}
		else
		{
			return nullptr;
		}
	}
}