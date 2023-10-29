#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/logging/log.hpp>

#include <engine/scene/common_types.hpp>

#include <engine/scene/objects/basic_object_builder.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/entities/basic_entity.hpp>

#include <memory>



namespace engine::scene
{
	class Scene: private util::noconstructible
	{
	public:

		using object_builder_ptr_t = std::shared_ptr<basic_object_builder>;
		using object_ptr_t = std::shared_ptr<ecs::entities::basic_entity>;
		template <typename T>
		using component_ptr_t = ecs::components::components_manager::component_ptr_t<T>;
		template <typename T>
		using components_range_t = ecs::components::components_manager::components_range_t<T>;





		template <typename T, typename ...Args>
		static object_id_t addObject(const object_builder_ptr_t& _obj_builder = nullptr, Args&& ..._args) noexcept;

		static bool delObject(object_id_t _obj_id) noexcept;

		static [[nodiscard]] object_ptr_t getObject(object_id_t _obj_id) noexcept;

		template <typename T, typename ...Args>
		static bool addComponent(object_id_t _obj_id, Args&& ..._args) noexcept;

		template <typename T>
		static [[nodiscard]] component_ptr_t<T> getComponent(object_id_t _obj_id) noexcept;

		template <typename T>
		static [[nodiscard]] component_ptr_t<T> getComponent() noexcept;

		template <typename T>
		static [[nodiscard]] std::optional<components_range_t<T>> getComponents() noexcept;

		template <typename T>
		static void enableComponent(object_id_t _obj_id) noexcept;

		template <typename T>
		static void disableComponent(object_id_t _obj_id) noexcept;

		template <typename T>
		static bool hasComponent(object_id_t _obj_id) noexcept;



		template <typename T, typename ...Args>
		static bool addSystem(Args ..._args) noexcept;

		template <typename T>
		static bool delSystem() noexcept;

		template <typename T>
		static void enableSystem() noexcept;

		template <typename T>
		static void disableSystem() noexcept;



		static bool initialize() noexcept;
		static void update(float _delta_time) noexcept;
		static void terminate() noexcept;

	};





	template <typename T, typename ...Args>
	object_id_t Scene::addObject(const object_builder_ptr_t& _obj_builder, Args&& ..._args) noexcept
	{
		auto ID = ecs::ECS::instance().getEntitiesManager()->createEntity<T>(std::forward<Args>(_args)...);
		if (ID == ecs::entities::INVALID_ENTITY_ID)
		{
			LOG_WARN("[Scene WARN] Can't create object");
			return ID;
		}

		if (_obj_builder)
			_obj_builder->build(ID);

		return ID;
	}





	template <typename T, typename ...Args>
	bool Scene::addComponent(object_id_t _obj_id, Args&& ..._args) noexcept
	{
		return ecs::ECS::instance().getComponentsManager()->addComponent<T>(_obj_id, std::forward<Args>(_args)...);
	}



	template <typename T>
	static Scene::component_ptr_t<T> Scene::getComponent(object_id_t _obj_id) noexcept
	{
		return ecs::ECS::instance().getComponentsManager()->getComponent<T>(_obj_id);
	}



	template <typename T>
	static Scene::component_ptr_t<T> Scene::getComponent() noexcept
	{
		return ecs::ECS::instance().getComponentsManager()->getComponent<T>();
	}



	template <typename T>
	static std::optional<Scene::components_range_t<T>> Scene::getComponents() noexcept
	{
		return ecs::ECS::instance().getComponentsManager()->getComponents<T>();
	}



	template <typename T>
	void Scene::enableComponent(object_id_t _obj_id) noexcept
	{
		ecs::ECS::instance().getEntitiesManager()->getEntity(_obj_id)->enableComponent<T>();
	}



	template <typename T>
	void Scene::disableComponent(object_id_t _obj_id) noexcept
	{
		ecs::ECS::instance().getEntitiesManager()->getEntity(_obj_id)->disableComponent<T>();
	}



	template <typename T>
	bool Scene::hasComponent(object_id_t _obj_id) noexcept
	{
		ecs::ECS::instance().getEntitiesManager()->getEntity(_obj_id)->hasComponent<T>();
	}





	template <typename T, typename ...Args>
	bool Scene::addSystem(Args ..._args) noexcept
	{
		return ecs::ECS::instance().getSystemsManager()->addSystem<T>(std::forward<Args>(_args)...);
	}



	template <typename T>
	bool Scene::delSystem() noexcept
	{
		return ecs::ECS::instance().getSystemsManager()->removeSystem<T>();
	}



	template <typename T>
	void Scene::enableSystem() noexcept
	{
		return ecs::ECS::instance().getSystemsManager()->enableSystem<T>();
	}



	template <typename T>
	void Scene::disableSystem() noexcept
	{
		return ecs::ECS::instance().getSystemsManager()->disableSystem<T>();
	}
}