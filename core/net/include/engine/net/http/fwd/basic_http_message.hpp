#pragma once

#include <concepts>
#include <string>



namespace engine::net::http
{
	template <typename T>
	concept http_body = requires (T _body, std::string _body_str) {
		typename T::body_t;
		{ _body.parse(_body_str) } -> std::convertible_to<bool>;
		{ _body.get() } -> std::convertible_to<typename T::body_t>;
		{ _body } -> std::convertible_to<std::string>;
	} && std::is_default_constructible_v<typename T::body_t> && std::is_copy_constructible_v<typename T::body_t>;



	template <http_body T>
	class basic_http_message;
}