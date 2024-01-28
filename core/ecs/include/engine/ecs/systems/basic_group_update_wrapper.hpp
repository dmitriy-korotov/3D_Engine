#pragma once

#include <memory>



namespace engine::ecs::systems
{
	class basic_group_update_wrapper
	{
	public:
		
		virtual ~basic_group_update_wrapper() = default;

		virtual void preUpdate(float _delta_time) noexcept = 0;
		virtual void postUpdate(float _delta_time) noexcept = 0;

	};

	using group_update_wrapper_ptr_t = std::unique_ptr<basic_group_update_wrapper>;
}