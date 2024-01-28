#pragma once

#include <engine/scene/Scene.hpp>



namespace engine::scene::systems
{
	class render final: public scene_system
	{
	public:

		static constexpr std::string_view system_name = "render";

		void preUpdate(float _delta_time) noexcept override;
		void update(float _delta_time) noexcept override;

		serialized_view_t serialize() const override;

	};
}