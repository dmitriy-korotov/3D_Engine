#pragma once

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/util/nocopyeble.hpp>

#include <unordered_map>
#include <memory>
#include <optional>



namespace engine::ecs::components
{
	class basic_component;
}



namespace engine::ecs::entities
{
	template <typename ComponentType>
	using component_ptr = std::weak_ptr<ComponentType>;

	class entities_manager;



	class basic_entity: private util::nocopyeble
	{
	public:

		friend entities_manager;
		friend components::components_manager;

		basic_entity() noexcept;
		virtual ~basic_entity();

		entity_id getID() const noexcept;
		static entity_type_id getEntityTypeID() noexcept;

		template <typename ComponentType>
		std::optional<component_ptr<ComponentType>> getComponent() const noexcept;

		template <typename ComponentType, typename ...Args>
		void addComponent(Args&&... _args) noexcept;

	private:

		template <typename ComponentType>
		void addComponent(std::weak_ptr<ComponentType> _component) noexcept;

	private:

		static void setEntityTypeID(entity_type_id _entity_type_id) noexcept;
		static entity_id generateEntityId() noexcept;
		static entity_id m_next_entity_id;
		static entity_type_id m_entity_type_id;

	private:

		entity_id m_id = INVALID_ENTITY_ID;
		std::unordered_map<std::string_view, component_ptr<components::basic_component>> m_components;

	};





	template <typename ComponentType, typename ...Args>
	void basic_entity::addComponent(Args&&... _args) noexcept
	{
		ECS::instance().getComponentsManager()->addComponent<ComponentType>(m_id, _args...);
	}



	template <typename ComponentType>
	void basic_entity::addComponent(std::weak_ptr<ComponentType> _component) noexcept
	{
		m_components.emplace(ComponentType::component_name, std::move(_component));
	}



	template <typename ComponentType>
	std::optional<component_ptr<ComponentType>> basic_entity::getComponent() const noexcept
	{
		static_assert(std::is_base_of_v<components::basic_component, ComponentType>, "ComponentType is not derived basic_component");

		auto component = m_components.find(ComponentType::component_name);
		if (component != m_components.end())
		{
			std::shared_ptr<ComponentType> component_ptr = std::dynamic_pointer_cast<ComponentType>(component->second.lock());
			if (component_ptr != nullptr)
			{
				return component_ptr;
			}
		}
		return std::nullopt;
	}
}