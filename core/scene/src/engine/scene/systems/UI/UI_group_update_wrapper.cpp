#include <engine/scene/systems/UI/UI_group_update_wrapper.hpp>

#include <engine/Engine.hpp>



namespace engine::scene
{
	auto UI_group_update_wrapper::preUpdate([[maybe_unused]] float _delta_time) noexcept -> void
	{
		engine::Engine::getApplicationUIModule()->onUIDrawBegin();
	}



	auto UI_group_update_wrapper::postUpdate([[maybe_unused]] float _delta_time) noexcept -> void
	{
		engine::Engine::getApplicationUIModule()->onUIDrawEnd();
	}
}