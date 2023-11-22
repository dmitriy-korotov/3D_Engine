#pragma once

#include <engine/scene/Scene.hpp>

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>



namespace engine::scene::components
{
	class components_creator
	{
	public:

		using creatorfn_t = std::function<component_ptr_t<basic_component_t>(scene::object_id_t)>;
		using creatorfn_ptr_t = std::shared_ptr<creatorfn_t>;
		using creators_map_t = std::unordered_map<std::string, creatorfn_ptr_t>;

		static bool addComponentCreator(std::string _creator_name, creatorfn_t _creator) noexcept;

		static [[nodiscard]] creatorfn_ptr_t getComponentCreator(const std::string& _creator_name) noexcept;

	private:

		static creators_map_t m_creators;

	};



	template <SceneComponent T>
	void AddComponentCreator() noexcept
	{
		components_creator::addComponentCreator(std::string(T::component_name),
			[](scene::object_id_t _target) -> component_ptr_t<basic_component_t>
			{
				auto entity = scene::Scene::getObject(_target);
				entity->addComponent<T>();
				return entity->getComponent<T>();
			});
	}
}