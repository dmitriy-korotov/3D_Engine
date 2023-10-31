#pragma once

#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	class render final: public basic_system
	{
	public:

		static constexpr std::string_view system_name = "render";

		void preUpdate(float _delta_time) const noexcept override;
		void update(float _delta_time) const noexcept override;

		json dump() const override;

	};
}