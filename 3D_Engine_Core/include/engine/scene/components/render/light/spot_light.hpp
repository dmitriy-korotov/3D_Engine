#pragma once

#include <engine/scene/components/render/light/point_light.hpp>



namespace engine::scene::components
{
	class spot_light: public point_light
	{
	public:

		static constexpr std::string_view component_name = "spot_light";



		spot_light(float _radius = 1.f) noexcept;

		const glm::vec3& getDirection() const noexcept;

		void setRadius(float _radius) noexcept;
		float getRadius() const noexcept;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		float m_radius = 1.f;

	};
}