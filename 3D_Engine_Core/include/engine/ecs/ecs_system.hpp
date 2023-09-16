#pragma once

#include <engine/util/noconstructible.hpp>

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

	class ECS : private util::noconstructible
	{
	public:

		using entities_manager_ptr = std::unique_ptr<entities::entities_manager>;
		using components_manager_ptr = std::unique_ptr<components::components_manager>;

		static bool initialize() noexcept;
		static void terminate() noexcept;

		static const entities_manager_ptr& getEntitiesManager() noexcept;
		static const components_manager_ptr& getComponentsManager() noexcept;

		static void update(float _delta_time) noexcept;

	private:

		static entities_manager_ptr m_entities_manager;
		static components_manager_ptr m_components_manager;

	};
}