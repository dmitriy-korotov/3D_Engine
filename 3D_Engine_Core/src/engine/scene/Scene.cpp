#include <engine/scene/Scene.hpp>

#include <engine/logging/log.hpp>

#include <nlohmann/json.hpp>

#include <fstream>





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