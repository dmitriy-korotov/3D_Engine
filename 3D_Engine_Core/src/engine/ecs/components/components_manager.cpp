#include <engine/ecs/components/components_manager.hpp>



namespace engine::ecs::components
{
	void components_manager::removeAllComponents() noexcept
	{
		// TODO: detuch components from entities
		m_components.clear();
	}
}