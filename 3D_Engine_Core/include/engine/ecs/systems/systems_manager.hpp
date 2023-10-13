#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/systems/fwd/basic_system.hpp>

#include <set>
#include <memory>
#include <typeinfo>



namespace engine::ecs::systems
{
	class systems_manager: private util::nocopyeble
	{
	public:

		using system_ptr = std::shared_ptr<basic_system>;
		using systems_storage = std::set<std::pair<size_t, system_ptr>>;



		systems_manager() = default;
		~systems_manager();

		void update(float _delta_time);

		template <typename SystemType, typename ...Args>
		void addSystem(size_t _priority, Args&&... _args) noexcept;

		void removeAllSystems() noexcept;

	private:

		systems_storage m_systems;

	};



	template <typename SystemType, typename ...Args>
	void systems_manager::addSystem(size_t _priority, Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v<basic_system, SystemType>, "SystemType is not derived basic_system.");

		m_systems.emplace(_priority, std::make_shared<SystemType>(std::forward<Args>(_args)...));
	}
}