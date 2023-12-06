#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/systems/systems_manager.hpp>

#include <memory>
#include <cassert>



namespace engine::ecs
{
	template <entities::Entity E, components::Component C, systems::System S>
	class ECS: private util::nocopyeble
	{
	public:

		using entities_manager_ptr_t = std::unique_ptr<entities::entities_manager<E>>;
		using components_manager_ptr_t = std::unique_ptr<components::components_manager<C>>;
		using systems_manager_ptr_t = std::unique_ptr<systems::systems_manager<S>>;



		static ECS& instance() noexcept;



		bool initialize() noexcept;
		void terminate() noexcept;

		const entities_manager_ptr_t& getEntitiesManager() const noexcept;
		const components_manager_ptr_t& getComponentsManager() const noexcept;
		const systems_manager_ptr_t& getSystemsManager() const noexcept;

		void update(float _delta_time) noexcept;

	private:

		constexpr ECS() noexcept;

	private:

		entities_manager_ptr_t m_entities_manager = nullptr;
		components_manager_ptr_t m_components_manager = nullptr;
		systems_manager_ptr_t m_systems_manager = nullptr;

	};





	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::instance() noexcept -> ECS&
	{
		static ECS instance;
		return instance;
	}





	template <entities::Entity E, components::Component C, systems::System S>
	constexpr ECS<E, C, S>::ECS() noexcept
	{ }



	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::initialize() noexcept -> bool
	{
		m_entities_manager = std::make_unique<entities::entities_manager<E>>();
		m_components_manager = std::make_unique<components::components_manager<C>>();
		m_systems_manager = std::make_unique<systems::systems_manager<S>>();

		return true;
	}



	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::terminate() noexcept -> void
	{
		assert(m_entities_manager != nullptr && m_components_manager != nullptr && m_systems_manager != nullptr);

		m_components_manager->removeAllComponents();
		m_entities_manager->destroyAllEntities();
		m_systems_manager->removeAllSystems();
	}



	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::getEntitiesManager() const noexcept -> const entities_manager_ptr_t&
	{
		assert(m_entities_manager != nullptr);
		return m_entities_manager;
	}



	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::getComponentsManager() const noexcept -> const components_manager_ptr_t&
	{
		assert(m_components_manager != nullptr);
		return m_components_manager;
	}



	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::getSystemsManager() const noexcept -> const systems_manager_ptr_t&
	{
		assert(m_systems_manager != nullptr);
		return m_systems_manager;
	}



	template <entities::Entity E, components::Component C, systems::System S>
	auto ECS<E, C, S>::update(float _delta_time) noexcept -> void
	{
		assert(m_systems_manager != nullptr);
		m_systems_manager->update(_delta_time);
	}
}