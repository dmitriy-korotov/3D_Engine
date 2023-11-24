#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/scene/common_types.hpp>

#include <engine/scene/objects/basic_object_builder.hpp>

#include <glm/vec3.hpp>

#include <memory>
#include <filesystem>



namespace engine::scene
{
	using std::filesystem::path;



	namespace objects
	{
		class scene_object: public virtual ecs::entities::basic_entity, public interfaces::serializable_object
		{
		public:

			scene_object(const glm::vec3& _position = glm::vec3(0.f)) noexcept;

			template <ecs::components::Component T>
			std::shared_ptr<T> getComponent() const noexcept;

			template <ecs::components::Component T>
			void enableComponent() const noexcept;

			template <ecs::components::Component T>
			void disableComponent() const noexcept;

			template <ecs::components::Component T>
			bool hasComponent() const noexcept;

			template <ecs::components::Component T, typename ...Args>
			bool addComponent(Args&&... _args) noexcept;

			serialized_view_t serialize() const final;
			void deserializeFrom(const serialized_view_t& _serialized_view) final;

		};
	}



	namespace components
	{
		class scene_component: public virtual ecs::components::basic_component, public interfaces::serializable_object
		{
		public:

			static constexpr std::string_view component_name = "scene_component";

			serialized_view_t serialize() const;
			void deserializeFrom(const serialized_view_t& _serialized_view);

		};
	}



	namespace systems
	{
		class scene_system: public ecs::systems::basic_system, public interfaces::serializable_object
		{
		public:

			static constexpr std::string_view system_name = "scene_system";

			serialized_view_t serialize() const;
			void deserializeFrom(const serialized_view_t& _serialized_view);

		};
	}





	template <typename T>
	concept SceneObject = std::derived_from<T, basic_object_t> || std::is_same_v<T, basic_object_t>;

	template <typename T>
	concept SceneComponent = std::derived_from<T, basic_component_t> || std::is_same_v<T, basic_component_t>;

	template <typename T>
	concept SceneSystem = std::derived_from<T, basic_system_t> || std::is_same_v<T, basic_system_t>;





	using object_builder_ptr_t = std::shared_ptr<objects::basic_object_builder>;

	template <SceneObject T>
	using object_ptr_t = std::shared_ptr<T>;

	template <SceneSystem T>
	using system_ptr_t = std::shared_ptr<T>;

	template <SceneComponent T>
	using component_ptr_t = std::shared_ptr<T>;

	template <SceneComponent T>
	using components_range_t = ecs::components::components_manager<basic_component_t>::components_range_t<T>;




	
	class Scene: private util::noconstructible
	{
	public:

		using ECS = ecs::ECS<basic_object_t, basic_component_t, basic_system_t>;



		template <SceneObject T, typename ...Args>
		static object_ptr_t<basic_object_t> addObject(Args&&... _args) noexcept;

		template <SceneObject T, typename Builder, typename ...Args>
		static object_ptr_t<basic_object_t> addObject(const object_builder_ptr_t& _obj_builder, Args&&... _args) noexcept;

		static bool delObject(object_id_t _obj_id) noexcept;

		static [[nodiscard]] object_ptr_t<basic_object_t> getObject(object_id_t _obj_id) noexcept;



		template <SceneComponent T, typename ...Args>
		static component_ptr_t<T> addComponent(object_id_t _obj_id, Args&&... _args) noexcept;

		template <SceneComponent T>
		static [[nodiscard]] component_ptr_t<T> getComponent(object_id_t _obj_id) noexcept;

		template <SceneComponent T>
		static [[nodiscard]] component_ptr_t<T> getComponent() noexcept;

		template <SceneComponent T>
		static [[nodiscard]] std::optional<components_range_t<T>> getComponents() noexcept;

		template <SceneComponent T>
		static void enableComponent(object_id_t _obj_id) noexcept;

		template <SceneComponent T>
		static void disableComponent(object_id_t _obj_id) noexcept;

		template <SceneComponent T>
		static bool hasComponent(object_id_t _obj_id) noexcept;



		template <SceneSystem T, typename ...Args>
		static system_ptr_t<basic_system_t> addSystem(Args&&... _args) noexcept;

		template <SceneSystem T>
		static bool delSystem() noexcept;

		template <SceneSystem T>
		static void enableSystem() noexcept;

		template <SceneSystem T>
		static void disableSystem() noexcept;



		static bool initialize() noexcept;
		static void update(float _delta_time) noexcept;
		static void terminate() noexcept;



		static bool load(const path& _path) noexcept;
		static bool save(const path& _path) noexcept;

	private:

		static ECS& m_entity_component_system;

	};





	template <SceneObject T, typename ...Args>
	auto Scene::addObject(Args&&... _args) noexcept -> object_ptr_t<basic_object_t>
	{
		return addObject<T, objects::basic_object_builder>(object_builder_ptr_t(nullptr), std::forward<Args>(_args)...);
	}



	template <SceneObject T, typename Builder, typename ...Args>
	auto Scene::addObject(const object_builder_ptr_t& _obj_builder, Args&&... _args) noexcept -> object_ptr_t<basic_object_t>
	{
		auto object = m_entity_component_system.getEntitiesManager()->createEntity<T>(std::forward<Args>(_args)...);
		if (object == nullptr)
		{
			LOG_WARN("[Scene WARN] Can't create object");
			return nullptr;
		}

		if (_obj_builder)
			_obj_builder->build(object->getID());

		return object;
	}





	template <SceneComponent T, typename ...Args>
	auto Scene::addComponent(object_id_t _obj_id, Args&&... _args) noexcept -> component_ptr_t<T>
	{
		return m_entity_component_system.getComponentsManager()->addComponent<T>(_obj_id, std::forward<Args>(_args)...);
	}



	template <SceneComponent T>
	auto Scene::getComponent(object_id_t _obj_id) noexcept -> component_ptr_t<T>
	{
		return m_entity_component_system.getComponentsManager()->getComponent<T>(_obj_id);
	}



	template <SceneComponent T>
	auto Scene::getComponent() noexcept -> component_ptr_t<T>
	{
		return m_entity_component_system.getComponentsManager()->getComponent<T>();
	}



	template <SceneComponent T>
	auto Scene::getComponents() noexcept -> std::optional<components_range_t<T>>
	{
		return m_entity_component_system.getComponentsManager()->getComponents<T>();
	}



	template <SceneComponent T>
	auto Scene::enableComponent(object_id_t _obj_id) noexcept -> void
	{
		m_entity_component_system.getEntitiesManager()->getEntity(_obj_id)->enableComponent<T>();
	}



	template <SceneComponent T>
	auto Scene::disableComponent(object_id_t _obj_id) noexcept -> void
	{
		m_entity_component_system.getEntitiesManager()->getEntity(_obj_id)->disableComponent<T>();
	}



	template <SceneComponent T>
	auto Scene::hasComponent(object_id_t _obj_id) noexcept -> bool
	{
		m_entity_component_system.getEntitiesManager()->getEntity(_obj_id)->hasComponent<T>();
	}





	template <SceneSystem T, typename ...Args>
	auto Scene::addSystem(Args&&... _args) noexcept -> system_ptr_t<basic_system_t>
	{
		return m_entity_component_system.getSystemsManager()->addSystem<T>(std::forward<Args>(_args)...);
	}



	template <SceneSystem T>
	auto Scene::delSystem() noexcept -> bool
	{
		return m_entity_component_system.getSystemsManager()->removeSystem<T>();
	}



	template <SceneSystem T>
	auto Scene::enableSystem() noexcept -> void
	{
		return m_entity_component_system.getSystemsManager()->enableSystem<T>();
	}



	template <SceneSystem T>
	auto Scene::disableSystem() noexcept -> void
	{
		return m_entity_component_system.getSystemsManager()->disableSystem<T>();
	}
}