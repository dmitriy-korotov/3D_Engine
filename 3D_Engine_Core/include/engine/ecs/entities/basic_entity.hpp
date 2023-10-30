#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/ecs/entities/fwd/entities_manager.hpp>
#include <engine/ecs/components/fwd/basic_component.hpp>

#include <unordered_map>
#include <memory>



namespace engine::ecs::entities
{
	class basic_entity: private util::nocopyeble
	{
	public:

		friend entities_manager;
		friend components::components_manager;



		template <typename ComponentType>
		using component_ptr_t = std::shared_ptr<ComponentType>;

		using components_map_t = std::unordered_map<std::string_view, component_ptr_t<components::basic_component>>;



		basic_entity() noexcept;
		virtual ~basic_entity();

		entity_id_t getID() const noexcept;

		template <typename ComponentType>
		component_ptr_t<ComponentType> getComponent() const noexcept;

		template <typename ComponentType>
		void enableComponent() const noexcept;

		template <typename ComponentType>
		void disableComponent() const noexcept;

		template <typename ComponentType>
		bool hasComponent() const noexcept;

		template <typename ComponentType, typename ...Args>
		bool addComponent(Args&&... _args) noexcept;

	private:

		template <typename ComponentType>
		bool addComponent(component_ptr_t<ComponentType> _component) noexcept;

	private:

		static entity_id_t generateEntityId() noexcept;
		static entity_id_t m_next_entity_id;

	private:

		entity_id_t m_id = INVALID_ENTITY_ID;
		components_map_t m_components;

	};





	template <typename ComponentType, typename ...Args>
	bool basic_entity::addComponent(Args&&... _args) noexcept
	{
		const auto& components_manager = ECS::instance().getComponentsManager();
		component_ptr_t<ComponentType> component = components_manager->addComponentNotConstructedEntity<ComponentType>(m_id, std::forward<Args>(_args)...);
		return addComponent(std::move(component));
	}



	template <typename ComponentType>
	bool basic_entity::addComponent(component_ptr_t<ComponentType> _component) noexcept
	{
		auto it = m_components.emplace(ComponentType::component_name, std::move(_component));
		return it.second;
	}



	template <typename ComponentType>
	basic_entity::component_ptr_t<ComponentType> basic_entity::getComponent() const noexcept
	{
		static_assert(std::is_base_of_v<components::basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = m_components.find(ComponentType::component_name);
		if (component != m_components.end())
			return std::dynamic_pointer_cast<ComponentType>(component->second);
		return nullptr;
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