#include <engine/scene/objects/scene_object.hpp>

#include <engine/scene/components/physic/position.hpp>





using namespace engine::scene::components;

namespace engine::scene::objects
{
	scene_object::scene_object(const glm::vec3& _position) noexcept
	{
		addComponent<position>(_position);
	}




	auto scene_object::serialize() const -> serialized_view_t
	{
		serialized_view_t serialize_view;

		serialize_view["id"] = m_id;

		return serialize_view;
	}



	auto scene_object::deserializeFrom(const serialized_view_t& _serialized_view) -> void
	{
		_serialized_view.at("id").get_to(m_id);
	}
}