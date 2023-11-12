#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/components/fwd/components_manager.hpp>
#include <engine/ecs/entities/fwd/entities_manager.hpp>
#include <engine/ecs/systems/fwd/systems_manager.hpp>

#include <memory>



namespace engine::ecs
{
	class ECS: private util::nocopyeble
	{
	public:

		using entities_manager_ptr_t = std::unique_ptr<entities::entities_manager>;
		using components_manager_ptr_t = std::unique_ptr<components::components_manager>;
		using systems_manager_ptr_t = std::unique_ptr<systems::systems_manager>;



		static ECS& instance() noexcept;



		bool initialize() noexcept;
		void terminate() noexcept;

		const entities_manager_ptr_t& getEntitiesManager() const noexcept;
		const components_manager_ptr_t& getComponentsManager() const noexcept;
		const systems_manager_ptr_t& getSystemsManager() const noexcept;

		void update(float _delta_time) noexcept;

	private:

		ECS() noexcept;

	private:

		entities_manager_ptr_t m_entities_manager;
		components_manager_ptr_t m_components_manager;
		systems_manager_ptr_t m_systems_manager;

	};
}