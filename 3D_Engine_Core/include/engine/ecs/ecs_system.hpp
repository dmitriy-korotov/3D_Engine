#pragma once

#include <engine/util/nocopyeble.hpp>

#include <memory>



namespace engine::ecs
{
	namespace entities
	{
		class entities_manager;
	}

	namespace components
	{
		class components_manager;
	}

	namespace systems
	{
		class systems_manager;
	}

	class ECS: private util::nocopyeble
	{
	public:

		using entities_manager_ptr = std::unique_ptr<entities::entities_manager>;
		using components_manager_ptr = std::unique_ptr<components::components_manager>;
		using systems_manager_ptr = std::unique_ptr<systems::systems_manager>;

		static ECS& instance() noexcept;

		bool initialize() noexcept;
		void terminate() noexcept;

		const entities_manager_ptr& getEntitiesManager() const noexcept;
		const components_manager_ptr& getComponentsManager() const noexcept;
		const systems_manager_ptr& getSystemsManager() const noexcept;

		void update(float _delta_time) noexcept;

	private:

		ECS() noexcept;

	private:

		entities_manager_ptr m_entities_manager;
		components_manager_ptr m_components_manager;
		systems_manager_ptr m_systems_manager;

	};
}