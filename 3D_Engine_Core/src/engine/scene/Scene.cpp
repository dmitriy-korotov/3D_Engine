#include <engine/scene/Scene.hpp>

#include <engine/ecs/systems/systems_creator.hpp>
#include <engine/ecs/systems/systems_manager.hpp>

#include <engine/logging/log.hpp>

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>





using namespace nlohmann;

namespace engine::scene
{
	bool Scene::delObject(object_id_t _obj_id) noexcept
	{
		return ecs::ECS::instance().getEntitiesManager()->destroyEntity(_obj_id);
	}



	auto Scene::getObject(object_id_t _obj_id) noexcept -> object_ptr_t
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

			auto& systems = serialized_scene["systems"];
			for (auto it = systems.begin(); it != systems.end(); it++)
			{
				LOG_INFO("{}", std::string(it->at("system_name")));
				auto system_creator = ecs::systems::systems_creator::getCreator(std::string(it->at("system_name")));
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



		for (auto& entity : ecs::ECS::instance().getEntitiesManager()->getEntities())
		{
			auto dumped_view = entity.second->dump();
			entities_array.push_back(std::move(dumped_view));
		}

		for (auto& component : ecs::ECS::instance().getComponentsManager()->getComponents())
		{
			auto dumped_view = component->dump();
			components_array.push_back(std::move(dumped_view));
		}

		for (auto& system : ecs::ECS::instance().getSystemsManager()->getSystems())
		{
			auto dumped_view = system.second.second->dump();
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