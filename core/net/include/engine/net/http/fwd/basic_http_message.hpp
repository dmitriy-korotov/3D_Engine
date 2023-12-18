#pragma once

#include <concepts>
#include <string>



namespace engine::net::http
{
	template <typename T>
	concept http_body =
		(std::constructible_from<T, std::string&&> || std::constructible_from<T, const std::string&>) &&
		(std::is_copy_constructible_v<T> || std::is_move_constructible_v<T>) &&
		(std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>) &&
		std::is_destructible_v<T> &&
		std::is_class_v<typename T::body_t> &&
		requires (T _body)
	{
		{ _body.success() } -> std::convertible_to<bool>;
		{ _body.get() } -> std::convertible_to<const typename T::body_t&>;
		{ std::move(_body).get() } -> std::convertible_to<typename T::body_t&&>;
		{ _body } -> std::convertible_to<std::string>;
	};



	template <http_body T>
	class basic_http_message;
}