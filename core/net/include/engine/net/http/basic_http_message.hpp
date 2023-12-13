#pragma once

#include <engine/net/http/fwd/basic_http_message.hpp>

#include <unordered_map>



namespace engine::net::http
{
	enum class http_header : uint8_t
	{
		content_lenth,
		host,
		content_type,
		keep_alive,
		cookie,
	};



	template <http_body T>
	class basic_http_message
	{
	public:

		basic_http_message() = default;

		bool emplaceHeader(std::string _header, std::string _value) noexcept;
		bool emplaceHeader(http_header _key, std::string _value) noexcept;

		bool setBody(T&& _body) noexcept;
		bool setBody(const T& _body) noexcept;

		T&& getBody() && noexcept;
		const T& getBody() const & noexcept;

		void prepair() noexcept;

	private:

		using headers_t = std::unordered_map<std::string, std::string>;

		headers_t m_headers;

		T m_body;

	};




	std::string toString(http_header _header) noexcept;



	template <http_body T>
	auto basic_http_message<T>::emplaceHeader(std::string _header, std::string _value) noexcept -> bool
	{
		return m_headers.emplace(std::move(_header), std::move(_value)).second;
	}



	template <http_body T>
	auto basic_http_message<T>::emplaceHeader(http_header _key, std::string _value) noexcept -> bool
	{
		return emplaceHeader(toString(_key), std::move(_value));
	}



	template <http_body T>
	auto basic_http_message<T>::setBody(T&& _body) noexcept -> bool
	{
		m_body = std::forward<T>(_body);
	}



	template <http_body T>
	auto basic_http_message<T>::setBody(const T& _body) noexcept -> bool
	{
		m_body = _body;
	}




	template <http_body T>
	auto basic_http_message<T>::getBody() && noexcept -> T&&
	{
		return std::move(m_body);
	}



	template <http_body T>
	auto basic_http_message<T>::getBody() const & noexcept -> const T&
	{
		return m_body;
	}
}