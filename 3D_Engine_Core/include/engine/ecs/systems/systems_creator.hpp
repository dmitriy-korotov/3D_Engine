#pragma once

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/systems/systems_manager.hpp>

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>



namespace engine::ecs::systems
{
	class systems_creator
	{
	public:

		using creatorfn_t = std::function<void()>;
		using creatorfn_ptr_t = std::shared_ptr<creatorfn_t>;
		using creators_map_t = std::unordered_map<std::string, creatorfn_ptr_t>;

		static bool addCreator(std::string _system_name, creatorfn_t _creator_function) noexcept;

		static [[nodiscard]] creatorfn_ptr_t getCreator(const std::string& _system_name) noexcept;

	private:

		static creators_map_t m_creators;

	};



	template <typename System>
	void AddSystemCreator(size_t _priority) noexcept
	{
		static_assert(std::is_base_of_v<systems::basic_system, System>, "System is not inherited from 'basic_system'");
		systems_creator::addCreator(std::string(System::system_name),
			[_priority]() -> void
			{
				ECS::instance().getSystemsManager()->addSystem<System>(_priority);
			});
	}

}