#include <engine/scene/Scene.hpp>

#include <engine/scene/systems/systems_creator.hpp>
#include <engine/ecs/systems/systems_manager.hpp>

#include <engine/scene/components/components_creator.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/logging/log.hpp>

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>





using namespace nlohmann;

namespace engine::scene
{
	Scene::ECS& Scene::m_entity_component_system = Scene::ECS::instance();





	auto Scene::delObject(object_id_t _obj_id) noexcept -> bool
	{
		return m_entity_component_system.getEntitiesManager()->destroyEntity(_obj_id);
	}



	auto Scene::getObject(object_id_t _obj_id) noexcept -> object_ptr_t<basic_object_t>
	{
		return m_entity_component_system.getEntitiesManager()->getEntity(_obj_id);
	}



	bool Scene::addSystemsGroup(const std::string& _group_name, size_t _group_priority, 
								ecs::systems::group_update_wrapper_ptr_t _update_wrapper) noexcept
	{
		return m_entity_component_system.getSystemsManager()->addSystemsGroup(_group_name, _group_priority, std::move(_update_wrapper));
	}



	bool Scene::delSystemsGroup(const std::string& _group_name) noexcept
	{
		return m_entity_component_system.getSystemsManager()->removeSystemsGroup(_group_name);
	}



	void Scene::enableSystemsGroup(const std::string& _group_name) noexcept
	{
		m_entity_component_system.getSystemsManager()->enableGroup(_group_name);
	}



	void Scene::disableSystemsGroup(const std::string& _group_name) noexcept
	{
		m_entity_component_system.getSystemsManager()->disableGroup(_group_name);
	}



	auto Scene::initialize() noexcept -> bool
	{
		return m_entity_component_system.initialize();
	}



	auto Scene::update(float _delta_time) noexcept -> void
	{
		m_entity_component_system.update(_delta_time);
	}



	auto Scene::terminate() noexcept -> void
	{
		m_entity_component_system.terminate();
	}



	auto Scene::load(const path& _path) noexcept -> bool
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
				auto object = addObject<basic_object_t>();
				if (object != nullptr)
					object->deserializeFrom(*it);
				else
					LOG_WARN("[Scene WARN] Entity with ID '{0}' is not created", static_cast<int>(it->at("id")));
			}

			auto& components = serialized_scene["components"];
			for (auto it = components.begin(); it != components.end(); it++)
			{
				LOG_INFO("Component: {0}", std::string(it->at("component_name")));
				auto component_creator = components::components_creator::getComponentCreator(it->at("component_name"));
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
				auto system_creator = systems::systems_creator::getSystemCreator(std::string(it->at("system_name")));
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



	auto Scene::save(const path& _path) noexcept -> bool
	{
		json serialize_view;

		serialize_view["entities"] =	json::array();
		serialize_view["components"] =	json::array();
		serialize_view["systems"] =		json::array();

		auto& entities_array = serialize_view.at("entities");
		auto& systems_array = serialize_view.at("systems");
		auto& components_array = serialize_view.at("components");



		for (auto& entity : m_entity_component_system.getEntitiesManager()->getEntities())
		{
			auto dumped_view = entity.second->serialize();
			entities_array.push_back(std::move(dumped_view));
		}

		for (auto& component : m_entity_component_system.getComponentsManager()->getComponents())
		{
			auto dumped_view = component->serialize();
			components_array.push_back(std::move(dumped_view));
		}

		for (auto& system : m_entity_component_system.getSystemsManager()->getSystems())
		{
			auto dumped_view = system->serialize();
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