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

		static bool initialize() noexcept;
		static void terminate() noexcept;

	private:

		static std::unique_ptr<entities::entities_manager> m_entities_manager;
		static std::unique_ptr<components::components_manager> m_components_manager;

	};
}