#include <engine/scene/Scene.hpp>

#include <engine/ecs/systems/systems_creator.hpp>
#include <engine/ecs/systems/systems_manager.hpp>

#include <engine/ecs/components/components_creator.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/logging/log.hpp>

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>





using namespace nlohmann;

namespace engine::scene
{
	Scene::ECS& entity_component_system = Scene::ECS::instance();





	bool Scene::delObject(object_id_t _obj_id) noexcept
	{
		return entity_component_system.getEntitiesManager()->destroyEntity(_obj_id);
	}



	auto Scene::getObject(object_id_t _obj_id) noexcept -> object_ptr_t
	{
		return entity_component_system.getEntitiesManager()->getEntity(_obj_id);
	}



	bool Scene::initialize() noexcept
	{
		return entity_component_system.initialize();
	}



	void Scene::update(float _delta_time) noexcept
	{
		entity_component_system.update(_delta_time);
	}



	void Scene::terminate() noexcept
	{
		entity_component_system.terminate();
	}



	bool Scene::load(const path& _path) noexcept
	{
		if (!std::filesystem::exists(_path))
		{
			LOG_ERROR("[Scene ERROR] Can't find scene file '{0}'", _path.generic_string());
			return false;
		}

		std::ifstream file(_path);
		if (!file.is_open())
		{
			LOG_ERROR("[Scene ERROR] Can't open scene file '{0}'", _path.generic_string());
			return false;
		}

		try
		{
			json serialized_scene;
			file >> serialized_scene;

			auto& entities = serialized_scene["entities"];
			for (auto it = entities.begin(); it != entities.end(); it++)
			{
				LOG_INFO("Entity ID: {0}", static_cast<int>(it->at("id")));
				auto object = entity_component_system.getEntitiesManager()->createEntity<ecs::entities::basic_entity>();
				if (object != nullptr)
					object->deserializeFrom(*it);
				else
					LOG_WARN("[Scene WARN] Entity with ID '{0}' is not created", static_cast<int>(it->at("id")));
			}

			auto& components = serialized_scene["components"];
			for (auto it = components.begin(); it != components.end(); it++)
			{
				LOG_INFO("Component: {0}", std::string(it->at("component_name")));
				auto component_creator = ecs::components::components_creator::getComponentCreator(it->at("component_name"));
				if (component_creator != nullptr)
				{
					auto component = std::invoke(*component_creator, static_cast<size_t>(it->at("owner")));
					component->deserializeFrom(*it);
				}
				else
				{
					LOG_WARN("[Scene WARN] Component '{0}' is not created", std::string(it->at("component_name")));
				}
			}

			auto& systems = serialized_scene["systems"];
			for (auto it = systems.begin(); it != systems.end(); it++)
			{
				LOG_INFO("System: {0}", std::string(it->at("system_name")));
				auto system_creator = ecs::systems::systems_creator::getCreator(std::string(it->at("system_name")));
				if (system_creator != nullptr)
					(*system_creator)();
			}
		}
		catch (const std::exception& _ex)
		{
			LOG_ERROR("[Scene ERROR] Parse error: {0}", std::string(_ex.what()));
			return false;
		}

		return true;
	}



	bool Scene::save(const path& _path) noexcept
	{
		json serialize_view;

		serialize_view["entities"] =	json::array();
		serialize_view["components"] =	json::array();
		serialize_view["systems"] =		json::array();

		auto& entities_array = serialize_view.at("entities");
		auto& systems_array = serialize_view.at("systems");
		auto& components_array = serialize_view.at("components");



		for (auto& entity : entity_component_system.getEntitiesManager()->getEntities())
		{
			auto dumped_view = entity.second->serialize();
			entities_array.push_back(std::move(dumped_view));
		}

		for (auto& component : entity_component_system.getComponentsManager()->getComponents())
		{
			auto dumped_view = component->serialize();
			components_array.push_back(std::move(dumped_view));
		}

		for (auto& system : entity_component_system.getSystemsManager()->getSystems())
		{
			auto dumped_view = system.second.second->serialize();
			systems_array.push_back(std::move(dumped_view));
		}



		std::ofstream file(_path);
		if (file.is_open())
		{
			file << serialize_view;
		}
		else
		{
			LOG_ERROR("[Scene ERROR] Can't open file '{0}' for saving", _path.generic_string());
			return false;
		}

		return true;
	}
}