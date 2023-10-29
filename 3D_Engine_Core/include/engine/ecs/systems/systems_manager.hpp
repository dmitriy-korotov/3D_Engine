#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/systems/fwd/basic_system.hpp>

#include <map>
#include <memory>
#include <string>



namespace engine::ecs::systems
{
	class systems_manager: private util::nocopyeble
	{
	public:

		using system_ptr_t = std::shared_ptr<basic_system>;
		using systems_storage_t = std::multimap<size_t, std::pair<std::string, system_ptr_t>>;



		systems_manager() = default;
		~systems_manager();

		void update(float _delta_time);

		template <typename SystemType, typename ...Args>
		bool addSystem(size_t _priority, Args&&... _args) noexcept;

		template <typename SystemType>
		bool removeSystem() noexcept;

		template <typename SystemType>
		void enableSystem() noexcept;

		template <typename SystemType>
		void disableSystem() noexcept;

		void removeAllSystems() noexcept;

	private:

		template <typename SystemType>
		systems_storage_t::iterator findSystem() noexcept;

	private:

		systems_storage_t m_systems;

	};



	template <typename SystemType, typename ...Args>
	bool systems_manager::addSystem(size_t _priority, Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v<basic_system, SystemType>, "SystemType is not derived basic_system.");

		auto system = std::make_shared<SystemType>(std::forward<Args>(_args)...);

		auto it = m_systems.emplace(_priority, std::make_pair(SystemType::system_name, std::move(system)));

		return it != m_systems.end();
	}



	template <typename SystemType>
	systems_manager::systems_storage_t::iterator
	systems_manager::findSystem() noexcept
	{
		static_assert(std::is_base_of_v<basic_system, SystemType>, "SystemType is not derived basic_system.");

		for (auto begin = m_systems.begin(); begin != m_systems.end(); begin++)
		{
			if (begin->second.first == SystemType::system_name)
				return begin;
		}
		return m_systems.end();
	}



	template <typename SystemType>
	bool systems_manager::removeSystem() noexcept
	{
		auto system = findSystem<SystemType>();
		if (system != m_systems.end())
		{
			auto it = m_systems.erase(system);
			return it != m_systems.end();
		}
		return false;
	}



	template <typename SystemType>
	void systems_manager::enableSystem() noexcept
	{
		auto system = findSystem<SystemType>();
		if (system != m_systems.end())
			system->second.second->enable();
	}



	template <typename SystemType>
	void systems_manager::disableSystem() noexcept
	{
		auto system = findSystem<SystemType>();
		if (system != m_systems.end())
			system->second.second->disable();
	}
}