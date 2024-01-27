#pragma once

#include <engine/scene/Scene.hpp>

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>



namespace engine::scene::systems
{
	class systems_creator
	{
	public:

		using creatorfn_t = std::function<system_ptr_t<basic_system_t>()>;
		using creatorfn_ptr_t = std::shared_ptr<creatorfn_t>;
		using creators_map_t = std::unordered_map<std::string, creatorfn_ptr_t>;

		static bool addCreator(std::string _system_name, creatorfn_t _creator_function) noexcept;

		static [[nodiscard]] creatorfn_ptr_t getSystemCreator(const std::string& _system_name) noexcept;

	private:

		static creators_map_t m_creators;

	};



	template <SceneSystem T>
	void AddSystemCreator(std::string _group_name, size_t _priority) noexcept
	{
		systems_creator::addCreator(std::string(T::system_name),
			[group_name = std::move(_group_name), _priority]() -> system_ptr_t<basic_system_t>
			{
				return Scene::addSystem<T>(group_name, _priority);
			});
	}

}