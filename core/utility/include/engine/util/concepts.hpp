#pragma once

#include <type_traits>



namespace engine::util
{
	template <typename T>
	concept is_awaitable = requires
	{
		typename std::decay_t<T>::value_type;
		typename std::decay_t<T>::executor_type;
	};
}