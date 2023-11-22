#pragma once

#include <engine/scene/Scene.hpp>

#include <concepts>



namespace engine::scene::objects
{
	template <ecs::components::Component T, typename ...Args>
	auto scene_object::addComponent(Args&&... _args) noexcept -> bool
	{
		auto component = Scene::addComponent<T>(m_id, std::forward<Args>(_args)...);
		return component != nullptr;

	}



	template <ecs::components::Component T>
	auto scene_object::getComponent() const noexcept -> std::shared_ptr<T>
	{
		return Scene::getComponent<T>(m_id);
	}



	template <ecs::components::Component T>
	auto scene_object::enableComponent() const noexcept -> void
	{
		Scene::enableComponent<T>(m_id);
	}



	template <ecs::components::Component T>
	auto scene_object::disableComponent() const noexcept -> void
	{
		Scene::disableComponent<T>(m_id);
	}



	template <ecs::components::Component T>
	auto scene_object::hasComponent() const noexcept -> bool
	{
		return Scene::hasComponent<T>(m_id);
	}
}