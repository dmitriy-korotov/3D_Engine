#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/ecs.hpp>

#include <engine/ecs/systems/fwd/systems_manager.hpp>

#include <string>



namespace engine::ecs::systems
{
	class basic_system: private util::nocopyeble
	{
	public:

		friend systems_manager;

		basic_system() = default;
		virtual ~basic_system() = default;

		virtual void preUpdate(float _delta_time) const noexcept;
		virtual void update(float _delta_time) const noexcept = 0;
		virtual void postUpdate(float _delta_time) const noexcept;

		bool isActive() const noexcept;
		void enable() noexcept;
		void disable() noexcept;

	private:

		bool m_is_active = true;

	};
}