#include <engine/scene/Scene.hpp>



namespace engine::scene::components
{
	auto scene_component::serialize() const -> serialized_view_t
	{
		serialized_view_t serialize_view;

		serialize_view["id"] = getID();
		serialize_view["is_active"] = isActive();
		serialize_view["owner"] = getOwner();

		return serialize_view;
	}



	auto scene_component::deserializeFrom(const serialized_view_t& _serialized_view) -> void
	{
		component_id_t id = 0;
		object_id_t owner_id = 0;
		bool is_active = false;

		_serialized_view.at("id").get_to(id);
		_serialized_view.at("is_active").get_to(is_active);
		_serialized_view.at("owner").get_to(owner_id);

		setID(id);
		setOwner(owner_id);

		if (is_active)
			enable();
		else
			disable();
	}
}