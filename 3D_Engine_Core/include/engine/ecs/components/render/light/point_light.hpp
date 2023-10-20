#pragma once

#include <engine/ecs/components/render/light/light.hpp>
#include <engine/ecs/components/render/light/light_attenuation.hpp>

#include <engine/ecs/components/physic/position.hpp>



namespace engine::ecs::components
{
	class point_light: public light,
					   public light_attenuation
	{
	public:

		static constexpr std::string_view component_name = "point_light";


		
		using light::light;

		glm::vec3 getPosition() const noexcept;

		bool putOnUI() noexcept override;

	};
}