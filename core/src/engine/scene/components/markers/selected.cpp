#include <engine/scene/components/markers/selected.hpp>



namespace engine::scene::components
{
	auto selected::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}