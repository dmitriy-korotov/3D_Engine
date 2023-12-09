#pragma once

#include <engine/scene/components/render/light/light.hpp>
#include <engine/scene/components/render/light/light_attenuation.hpp>

#include <engine/scene/components/physic/position.hpp>



namespace engine::scene::components
{
	class point_light: public light,
					   public light_attenuation
	{
	public:

		static constexpr std::string_view component_name = "point_light";


		
		using light::light;

		glm::vec3 getPosition() const noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	};
}