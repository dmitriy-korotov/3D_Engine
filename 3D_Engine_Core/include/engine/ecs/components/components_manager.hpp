#pragma once

#include <engine/ecs/ecs.hpp>

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
		using component_ptr = std::shared_ptr<basic_component>;
		using components_storage = std::unordered_map<component_type_id, std::vector<component_ptr>>;

		template <typename ComponentType, typename ...Args>
		void addComponent(entities::entity_id _entity_id, Args&&... _args) noexcept;

		template <typename ComponentType>
		std::optional<component_iterator<ComponentType>> getComponents() noexcept;

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
			std::vector<component_ptr> this_type_components_storage;
			this_type_components_storage.push_back(std::move(component));
			m_components.emplace(ComponentType::getComponentTypeID(), std::move(this_type_components_storage));
		}
		else
		{
			m_components.find(ComponentType::getComponentTypeID())->second.push_back(std::move(component));
		}
	}



	template <typename ComponentType>
	std::optional<components_manager::component_iterator<ComponentType>>
	components_manager::getComponents() noexcept
	{
		auto components_iter = m_components.find(ComponentType::getComponentTypeID());
		if (components_iter != m_components.end())
		{
			auto result = components_iter->second.begin();
			return *reinterpret_cast<components_manager::component_iterator<ComponentType>*>(&result);
		}
		else
		{
			return std::nullopt;
		}
	}
}