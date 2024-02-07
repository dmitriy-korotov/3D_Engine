#pragma once

#include <engine/util/nocopyeble.hpp>



namespace engine::util
{
	template <typename T>
	class singleton : private nocopyeble
	{
	public:

		static T& instance() noexcept;

	protected:

		singleton() = default;

	};



	template <typename T>
	auto singleton<T>::instance() noexcept -> T&
	{
		static T instance;
		return instance;
	}
}