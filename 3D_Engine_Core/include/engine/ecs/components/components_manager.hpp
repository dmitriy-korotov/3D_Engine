#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/ecs.hpp>

#include <engine/ecs/components/basic_component.hpp>
#include <engine/ecs/components/component_iterator.hpp>

#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include <concepts>



namespace engine::ecs::components
{
	template <Component UserBasicComponent>
	class components_manager: private util::nocopyeble
	{
	public:

		template <typename T>
		using component_ptr_t = std::shared_ptr<T>;

		template <typename T>
		using components_range_t = std::pair<component_iterator<UserBasicComponent, T>, component_iterator<UserBasicComponent, T>>;
		
		using components_map_t = std::unordered_map<entities::entity_id_t, component_ptr_t<UserBasicComponent>>;

		using components_storage_t = std::unordered_map<std::string_view, components_map_t>;

	public:

		template <std::derived_from<UserBasicComponent> T, typename ...Args>
		[[nodiscard]] component_ptr_t<T> addComponent(entities::entity_id_t _entity_id, Args&&... _args) noexcept;

		template <std::derived_from<UserBasicComponent> T>
		std::optional<components_range_t<T>> getComponents() const noexcept;

		std::vector<component_ptr_t<UserBasicComponent>> getComponents() const noexcept;

		template <std::derived_from<UserBasicComponent> T>
		[[nodiscard]] component_ptr_t<T> getComponent() const noexcept;

		template <std::derived_from<UserBasicComponent> T>
		[[nodiscard]] component_ptr_t<T> getComponent(entities::entity_id_t _entity_id) const noexcept;

		template <std::derived_from<UserBasicComponent> T>
		bool hasComponent(entities::entity_id_t _entity_id) const noexcept;

		template <std::derived_from<UserBasicComponent> T>
		void removeComponent(entities::entity_id_t _entity_id) noexcept;

		void removeAllComponents() noexcept;

	private:

		components_storage_t m_components;

	};





	template <Component UserBasicComponent>
	template <std::derived_from<UserBasicComponent> T, typename ...Args>
	auto components_manager<UserBasicComponent>::addComponent(entities::entity_id_t _entity_id, Args&&... _args) noexcept -> component_ptr_t<T>
	{
		auto component = std::make_shared<T>(std::forward<Args>(_args)...);
		component->setOwner(_entity_id);
		component->onConstruct();
		
		auto T_components_map = m_components.find(T::component_name);
		if (T_components_map == m_components.end())
		{
			components_map_t new_T_components_map;
			new_T_components_map.emplace(_entity_id, component);
			m_components.emplace(T::component_name, std::move(new_T_components_map));
		}
		else
		{
			m_components.find(T::component_name)->second.emplace(_entity_id, component);
		}
		return component;
	}



	template <Component UserBasicComponent>
	template <std::derived_from<UserBasicComponent> T>
	auto components_manager<UserBasicComponent>::removeComponent(entities::entity_id_t _entity_id) noexcept -> void
	{
		auto components_range = m_components.find(T::component_name);
		if (components_range != m_components.end())
			components_range->second.erase(_entity_id);
	}



	template <Component UserBasicComponent>
	template <std::derived_from<UserBasicComponent> T>
	auto components_manager<UserBasicComponent>::getComponents() const noexcept -> std::optional<components_range_t<T>>
	{
		auto components_range = m_components.find(T::component_name);
		if (components_range != m_components.end())
		{
			auto range_begin = components_range->second.begin();
			auto range_end = components_range->second.end();

			return std::make_pair(component_iterator<UserBasicComponent, T>(std::move(range_begin)),
								  component_iterator<UserBasicComponent, T>(std::move(range_end)));
		}
		return std::nullopt;
	}



	template <Component UserBasicComponent>
	template <std::derived_from<UserBasicComponent> T>
	auto components_manager<UserBasicComponent>::getComponent() const noexcept -> component_ptr_t<T>
	{
		auto components_range = m_components.find(T::component_name);
		if (components_range != m_components.end())
		{
			auto& components = components_range->second;

			if (components.size() > 1)
				LOG_WARN("[Components manager WARN] Components '{0}' more then one, returned first", T::component_name);

			if (components.size() == 1)
				return std::dynamic_pointer_cast<T>(components.begin()->second);
		}
		return nullptr;
	}



	template <Component UserBasicComponent>
	template <std::derived_from<UserBasicComponent> T>
	auto components_manager<UserBasicComponent>::getComponent(entities::entity_id_t _entity_id) const noexcept -> component_ptr_t<T>
	{
		auto components_range = m_components.find(T::component_name);
		if (components_range != m_components.end())
		{
			auto component_iter = components_range->second.find(_entity_id);

			if (component_iter != components_range->second.end())
				return std::dynamic_pointer_cast<T>(component_iter->second);
		}
		return nullptr;
	}



	template <Component UserBasicComponent>
	template <std::derived_from<UserBasicComponent> T>
	auto components_manager<UserBasicComponent>::hasComponent(entities::entity_id_t _entity_id) const noexcept -> bool
	{
		auto components_range = m_components.find(T::component_name);
		if (components_range != m_components.end())
		{
			auto component_iter = components_range->second.find(_entity_id);

			return (component_iter != components_range->second.end());
		}
		return false;
	}



	template <Component UserBasicComponent>
	auto components_manager<UserBasicComponent>::getComponents() const noexcept -> std::vector<component_ptr_t<UserBasicComponent>>
	{
		size_t components_count = 0;
		std::for_each(m_components.begin(), m_components.end(),
			[&components_count](const auto& _elem) -> void
			{
				components_count += _elem.second.size();
			});

		std::vector<component_ptr_t<UserBasicComponent>> components;
		components.reserve(components_count);

		for (auto& [comp_name, comps_storage] : m_components)
			for (auto& [ent_id, comp] : comps_storage)
				components.emplace_back(comp);

		return components;
	}



	template <Component UserBasicComponent>
	auto components_manager<UserBasicComponent>::removeAllComponents() noexcept -> void
	{
		m_components.clear();
	}
}