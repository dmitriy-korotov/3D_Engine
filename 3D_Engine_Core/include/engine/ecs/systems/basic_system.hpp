#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/util/nocopyeble.hpp>



namespace engine::ecs::systems
{
	class systems_manager;

	class basic_system: private util::nocopyeble
	{
	public:

		friend systems_manager;

		basic_system() = default;
		virtual ~basic_system() = default;

		virtual void update(float _delta_time) const noexcept = 0;

		static system_type_id getSystemTypeID() noexcept;

	private:

		static void setSystemTypeID(system_type_id _system_type_id) noexcept;

	private:

		static system_type_id m_system_type_id;

	};
}