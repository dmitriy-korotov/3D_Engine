#include <engine/ecs/components/markers/active_camera.hpp>



namespace engine::ecs::components
{
	auto active_camera::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}