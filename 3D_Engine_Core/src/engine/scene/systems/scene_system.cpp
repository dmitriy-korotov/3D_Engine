#include <engine/scene/Scene.hpp>



namespace engine::scene::systems
{
	auto scene_system::serialize() const -> serialized_view_t
	{
		serialized_view_t serialized_view;

		serialized_view["is_active"] = isActive();

		return serialized_view;
	}



	auto scene_system::deserializeFrom(const serialized_view_t& _serialized_view) -> void
	{
		bool is_active = false;
		_serialized_view.at("is_active").get_to(is_active);

		if (is_active)
			enable();
		else
			disable();
	}
}