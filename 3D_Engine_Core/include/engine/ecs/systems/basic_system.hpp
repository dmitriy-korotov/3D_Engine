#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/interfaces/serializable_object.hpp>

#include <string>
#include <concepts>



namespace engine::ecs::systems
{
	class basic_system: private util::nocopyeble
	{
	public:

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



	template <typename T>
	concept System = std::is_same_v<T, basic_system> || std::derived_from<T, basic_system> && requires {
		{ T::system_name } -> std::convertible_to<std::string_view>;
	};
}