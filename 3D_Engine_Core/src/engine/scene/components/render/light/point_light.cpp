#include <engine/scene/components/render/light/point_light.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/physic/position.hpp>

#include <engine/Engine.hpp>



namespace engine::scene::components
{
	auto point_light::getPosition() const noexcept -> glm::vec3
	{
		auto position_comp = Scene::getComponent<position>(getOwner());
		if (position_comp == nullptr)
		{
			LOG_ERROR("[Point light component ERROR] Entity hasn't 'position' component");
			return glm::vec3(0.f);
		}
		return position_comp->getPosition();
	}



	auto point_light::putOnUI() noexcept -> bool
	{
		bool is_clicked = false;

		is_clicked |= light::putOnUI();
		is_clicked |= light_attenuation::putOnUI();

		return is_clicked;
	}



	auto point_light::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view_light_attenuation = light_attenuation::serialize();
		auto serialized_view_light = light::serialize();

		serialized_view_t serialized_view_point_light = basic_component::serialize();

		serialized_view_point_light["component_name"] = component_name;

		serialized_view_point_light["components"] = { std::move(serialized_view_light_attenuation), std::move(serialized_view_light) };

		return serialized_view_point_light;
	}



	auto point_light::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		auto iter = _serialized_view.at("components").begin();
		light_attenuation::deserializeFrom(*iter);		iter++;
		light::deserializeFrom(*iter);
	}
}