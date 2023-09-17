#pragma once

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/util/nocopyeble.hpp>

#include <unordered_map>
#include <memory>



namespace engine::ecs::components
{
	class basic_component;
}



namespace engine::ecs::entities
{
	using component_ptr = std::weak_ptr<components::basic_component>;

	class entities_manager;



	class basic_entity : private util::nocopyeble
	{
	public:

		friend entities_manager;

		basic_entity() noexcept;
		virtual ~basic_entity();

		entity_id getID() const noexcept;

		template <typename ComponentType>
		const component_ptr& getComponent() const noexcept;

	protected:

		template <typename ComponentType, typename ...Args>
		void addComponent(Args&&... _args) noexcept;

	private:

		static entity_id generateEntityId() noexcept;
		static entity_id m_next_entity_id;

	private:

		entity_id m_id = INVALID_ENTITY_ID;
		std::unordered_map<components::component_type_id, component_ptr> m_components;

	};





	template <typename ComponentType, typename ...Args>
	void basic_entity::addComponent(Args&&... _args) noexcept
	{
		ECS::getComponentsManager()->addComponent<ComponentType>(m_id);
		auto component = ECS::getComponentsManager()->getComponent<ComponentType>(m_id);
		m_components.insert(ComponentType::getComponentTypeID(), component_ptr(component));
	}



	template <typename ComponentType>
	const component_ptr& basic_entity::getComponent() const noexcept
	{
		auto component = m_components.find(ComponentType::getComponentTypeID());
		if (component != m_components.end())
		{
			return *component;
		}
		else
		{
			nullptr;
		}
	}
}