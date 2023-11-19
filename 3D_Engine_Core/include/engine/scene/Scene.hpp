#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/logging/log.hpp>

#include <engine/scene/common_types.hpp>

#include <engine/scene/objects/basic_object_builder.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/systems/systems_manager.hpp>
#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/ecs/entities/basic_entity.hpp>

#include <memory>
#include <filesystem>



namespace engine::scene
{
	using std::filesystem::path;

	class Scene: private util::noconstructible
	{
	public:

		using entity_t = ecs::entities::basic_entity;
		using component_t = ecs::components::basic_component;
		using system_t = ecs::systems::basic_system;
		using ECS = ecs::ECS<entity_t, component_t, system_t>;

		using object_builder_ptr_t = std::shared_ptr<basic_object_builder>;
		using object_ptr_t = std::shared_ptr<ecs::entities::basic_entity>;
		using system_ptr_t = std::shared_ptr<ecs::systems::basic_system>;
		template <typename T>
		using component_ptr_t = ecs::components::components_manager<component_t>::component_ptr_t<T>;
		template <typename T>
		using components_range_t = ecs::components::components_manager<component_t>::components_range_t<T>;





		template <typename T, typename ...Args>
		static object_ptr_t addObject(Args&&... _args) noexcept;

		template <typename T, typename Builder, typename ...Args>
		static object_ptr_t addObject(const object_builder_ptr_t& _obj_builder, Args&&... _args) noexcept;

		static bool delObject(object_id_t _obj_id) noexcept;

		static [[nodiscard]] object_ptr_t getObject(object_id_t _obj_id) noexcept;

		template <typename T, typename ...Args>
		static component_ptr_t<T> addComponent(object_id_t _obj_id, Args&&... _args) noexcept;

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
		static system_ptr_t addSystem(Args&&... _args) noexcept;

		template <typename T>
		static bool delSystem() noexcept;

		template <typename T>
		static void enableSystem() noexcept;

		template <typename T>
		static void disableSystem() noexcept;



		static bool initialize() noexcept;
		static void update(float _delta_time) noexcept;
		static void terminate() noexcept;



		static bool load(const path& _path) noexcept;
		static bool save(const path& _path) noexcept;

	private:

		static ECS& entity_component_system;

	};





	template <typename T, typename ...Args>
	auto Scene::addObject(Args&&... _args) noexcept -> object_ptr_t
	{
		return addObject<T, basic_object_builder>(object_builder_ptr_t(nullptr), std::forward<Args>(_args)...);
	}



	template <typename T, typename Builder, typename ...Args>
	auto Scene::addObject(const object_builder_ptr_t& _obj_builder, Args&&... _args) noexcept -> object_ptr_t
	{
		auto object = entity_component_system.getEntitiesManager()->createEntity<T>(std::forward<Args>(_args)...);
		if (object == nullptr)
		{
			LOG_WARN("[Scene WARN] Can't create object");
			return nullptr;
		}

		if (_obj_builder)
			_obj_builder->build(object->getID());

		return object;
	}





	template <typename T, typename ...Args>
	auto Scene::addComponent(object_id_t _obj_id, Args&&... _args) noexcept -> component_ptr_t<T>
	{
		return entity_component_system.getComponentsManager()->addComponent<T>(_obj_id, std::forward<Args>(_args)...);
	}



	template <typename T>
	auto Scene::getComponent(object_id_t _obj_id) noexcept -> component_ptr_t<T>
	{
		return entity_component_system.getComponentsManager()->getComponent<T>(_obj_id);
	}



	template <typename T>
	auto Scene::getComponent() noexcept -> component_ptr_t<T>
	{
		return entity_component_system.getComponentsManager()->getComponent<T>();
	}



	template <typename T>
	auto Scene::getComponents() noexcept -> std::optional<components_range_t<T>>
	{
		return entity_component_system.getComponentsManager()->getComponents<T>();
	}



	template <typename T>
	void Scene::enableComponent(object_id_t _obj_id) noexcept
	{
		entity_component_system.getEntitiesManager()->getEntity(_obj_id)->enableComponent<T>();
	}



	template <typename T>
	void Scene::disableComponent(object_id_t _obj_id) noexcept
	{
		entity_component_system.getEntitiesManager()->getEntity(_obj_id)->disableComponent<T>();
	}



	template <typename T>
	bool Scene::hasComponent(object_id_t _obj_id) noexcept
	{
		entity_component_system.getEntitiesManager()->getEntity(_obj_id)->hasComponent<T>();
	}





	template <typename T, typename ...Args>
	auto Scene::addSystem(Args&&... _args) noexcept -> system_ptr_t
	{
		return entity_component_system.getSystemsManager()->addSystem<T>(std::forward<Args>(_args)...);
	}



	template <typename T>
	bool Scene::delSystem() noexcept
	{
		return entity_component_system.getSystemsManager()->removeSystem<T>();
	}



	template <typename T>
	void Scene::enableSystem() noexcept
	{
		return entity_component_system.getSystemsManager()->enableSystem<T>();
	}



	template <typename T>
	void Scene::disableSystem() noexcept
	{
		return entity_component_system.getSystemsManager()->disableSystem<T>();
	}
}