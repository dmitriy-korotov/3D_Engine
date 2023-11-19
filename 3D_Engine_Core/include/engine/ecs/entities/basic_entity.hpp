#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/interfaces/serializable_object.hpp>

#include <engine/ecs/ecs.hpp>
#include <engine/ecs/components/basic_component.hpp>

#include <unordered_map>
#include <concepts>
#include <memory>



namespace engine::ecs::entities
{
	class basic_entity: private util::nocopyeble, public interfaces::serializable_object
	{
	public:

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



		serialized_view_t serialize() const final;
		void deserializeFrom(const serialized_view_t& _serialized_view) final;

	private:

		static entity_id_t generateEntityId() noexcept;
		static entity_id_t m_next_entity_id;

	private:

		entity_id_t m_id = INVALID_ENTITY_ID;

	};



	template <typename T>
	concept Entity = std::derived_from<T, basic_entity> || std::is_same_v<T, basic_entity>;





	template <typename ComponentType, typename ...Args>
	bool basic_entity::addComponent(Args&&... _args) noexcept
	{
		//auto component = ECS::instance().getComponentsManager()->addComponent<ComponentType>(std::forward<Args>(_args)...);
		//return component;
		return true;
	}



	template <typename ComponentType>
	basic_entity::component_ptr_t<ComponentType> basic_entity::getComponent() const noexcept
	{
		return nullptr;
	}



	template <typename ComponentType>
	void basic_entity::enableComponent() const noexcept
	{
		
	}



	template <typename ComponentType>
	void basic_entity::disableComponent() const noexcept
	{
	
	}



	template <typename ComponentType>
	bool basic_entity::hasComponent() const noexcept
	{
		return true;
	}
}