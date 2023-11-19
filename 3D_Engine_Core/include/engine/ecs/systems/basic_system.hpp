#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/interfaces/serializable_object.hpp>

#include <string>
#include <concepts>



namespace engine::ecs::systems
{
	class basic_system: private util::nocopyeble, public interfaces::serializable_object
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

		serialized_view_t serialize() const override;
		void deserializeFrom(const serialized_view_t& _serialized_view) override;

	private:

		bool m_is_active = true;

	};



	template <typename T>
	concept System = std::is_same_v<T, basic_system> || std::derived_from<T, basic_system> && requires {
		{ T::system_name } -> std::convertible_to<std::string_view>;
	};
}