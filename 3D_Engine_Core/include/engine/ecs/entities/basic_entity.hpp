#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/ecs/entities/fwd/entities_manager.hpp>
#include <engine/ecs/components/fwd/basic_component.hpp>

#include <unordered_map>
#include <memory>
#include <optional>



namespace engine::ecs::entities
{
	template <typename ComponentType>
	using component_ptr = std::weak_ptr<ComponentType>;



	class basic_entity: private util::nocopyeble
	{
	public:

		friend entities_manager;
		friend components::components_manager;

		basic_entity() noexcept;
		virtual ~basic_entity();

		entity_id_t getID() const noexcept;

		template <typename ComponentType>
		std::optional<component_ptr<ComponentType>> getComponent() const noexcept; // need fix

		template <typename ComponentType>
		void enableComponent() const noexcept;

		template <typename ComponentType>
		void disableComponent() const noexcept;

		template <typename ComponentType>
		bool hasComponent() const noexcept;

		template <typename ComponentType, typename ...Args>
		void addComponent(Args&&... _args) noexcept;

	private:

		template <typename ComponentType>
		void addComponent(component_ptr<ComponentType> _component) noexcept;

	private:

		static entity_id_t generateEntityId() noexcept;
		static entity_id_t m_next_entity_id;

	private:

		entity_id_t m_id = INVALID_ENTITY_ID;
		std::unordered_map<std::string_view, component_ptr<components::basic_component>> m_components;

	};





	template <typename ComponentType, typename ...Args>
	void basic_entity::addComponent(Args&&... _args) noexcept
	{
		const auto& components_manager = ECS::instance().getComponentsManager();
		component_ptr<ComponentType> component = components_manager->addComponentNotConstructedEntity<ComponentType>(m_id, std::forward<Args>(_args)...);
		addComponent(std::move(component));
	}



	template <typename ComponentType>
	void basic_entity::addComponent(component_ptr<ComponentType> _component) noexcept
	{
		m_components.emplace(ComponentType::component_name, std::move(_component));
	}



	template <typename ComponentType>
	std::optional<component_ptr<ComponentType>> basic_entity::getComponent() const noexcept
	{
		static_assert(std::is_base_of_v<components::basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = m_components.find(ComponentType::component_name);
		if (component != m_components.end())
			return std::dynamic_pointer_cast<ComponentType>(component->second.lock());
		return std::nullopt;
	}



	template <typename ComponentType>
	void basic_entity::enableComponent() const noexcept
	{
		static_assert(std::is_base_of_v<components::basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = m_components.find(ComponentType::component_name);
		if (component != m_components.end())
			component->second->enable();
	}



	template <typename ComponentType>
	void basic_entity::disableComponent() const noexcept
	{
		static_assert(std::is_base_of_v<components::basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = m_components.find(ComponentType::component_name);
		if (component != m_components.end())
			component->second->disable();
	}



	template <typename ComponentType>
	bool basic_entity::hasComponent() const noexcept
	{
		static_assert(std::is_base_of_v<components::basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = m_components.find(ComponentType::component_name);
		return (component != m_components.end());
	}
}