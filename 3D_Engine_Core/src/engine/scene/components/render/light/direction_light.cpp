#include <engine/scene/components/render/light/direction_light.hpp>

#include <engine/Engine.hpp>



namespace engine::scene::components
{
	direction_light::direction_light(const glm::vec3& _direction, const glm::vec3& _ambient,
									 const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: light(_ambient, _diffuse, _specular)
			, direction(_direction)
	{ }



	auto direction_light::putOnUI() noexcept -> bool
	{
		bool is_clicked = false;

		is_clicked |= light::putOnUI();
		is_clicked |= direction::putOnUI();

		return is_clicked;
	}



	auto direction_light::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view_direction = direction::serialize();
		auto serialized_view_light = light::serialize();

		serialized_view_t serialized_view_direction_light = basic_component::serialize();

		serialized_view_direction_light["component_name"] = component_name;

		serialized_view_direction_light["components"] = { std::move(serialized_view_direction), std::move(serialized_view_light) };

		return serialized_view_direction_light;
	}



	auto direction_light::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		auto iter = _serialized_view.at("components").begin();
		direction::deserializeFrom(*iter);		iter++;
		light::deserializeFrom(*iter);
	}
}