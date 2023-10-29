#include <engine/scene/Scene.hpp>



namespace engine::scene
{
	bool Scene::delObject(object_id_t _obj_id) noexcept
	{
		return ecs::ECS::instance().getEntitiesManager()->destroyEntity(_obj_id);
	}



	Scene::object_ptr_t Scene::getObject(object_id_t _obj_id) noexcept
	{
		return ecs::ECS::instance().getEntitiesManager()->getEntity(_obj_id);
	}



	bool Scene::initialize() noexcept
	{
		return ecs::ECS::instance().initialize();
	}



	void Scene::update(float _delta_time) noexcept
	{
		ecs::ECS::instance().update(_delta_time);
	}



	void Scene::terminate() noexcept
	{
		ecs::ECS::instance().terminate();
	}
}