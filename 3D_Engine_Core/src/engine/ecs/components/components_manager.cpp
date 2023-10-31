#include <engine/ecs/components/components_manager.hpp>



namespace engine::ecs::components
{
	auto components_manager::getComponents() const noexcept -> std::vector<component_ptr_t<basic_component>>
	{
		size_t components_count = 0;
		std::for_each(m_components.begin(), m_components.end(),
			[&components_count](auto _elem) -> void
			{
				components_count += _elem.second.size();
			});

		std::vector<component_ptr_t<basic_component>> components;
		components.reserve(components_count);

		for (auto& [comp_name, comps_storage] : m_components)
			for (auto& [ent_id, comp] : comps_storage)
				components.emplace_back(comp);

		return components;
	}




	void components_manager::removeAllComponents() noexcept
	{
		m_components.clear();
	}
}