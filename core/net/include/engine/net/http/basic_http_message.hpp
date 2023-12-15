#pragma once

#include <engine/logging/log.hpp>

#include <engine/net/http/fwd/basic_http_message.hpp>

#include <unordered_map>
#include <sstream>



namespace engine::net::http
{
	enum class http_header : uint8_t
	{
		content_lenth,
		host,
		content_type,
		connection,
		cookie,
		encoding,
		date
	};



	struct http_version
	{
		uint8_t major = 1;
		uint8_t minor = 1;
	};



	template <http_body T>
	class basic_http_message
	{
	public:

		basic_http_message() = default;

		void setHttpVersion(http_version _version) noexcept;
		http_version getHttpVersion() const noexcept;

		bool emplaceHeader(std::string _header, std::string _value) noexcept;
		bool emplaceHeader(http_header _key, std::string _value) noexcept;

		bool setBody(T&& _body) noexcept;
		bool setBody(const T& _body) noexcept;

		T&& getBody() && noexcept;
		const T& getBody() const & noexcept;

		void prepare() noexcept;

		std::string build() const;

	protected:

		virtual std::string buildStartLine() const = 0;

	protected:

		using headers_t = std::unordered_map<std::string, std::string>;

		http_version m_version;
		headers_t m_headers;
		T m_body;

	};




	constexpr std::string toString(http_header _header) noexcept;

	constexpr bool isValidHttpVersion(http_version _version) noexcept;



	template <http_body T>
	auto basic_http_message<T>::setHttpVersion(http_version _version) noexcept -> void
	{
		if (!isValidHttpVersion(_version))
		{
			LOG_ERROR("[Basic http message ERROR] Invalid http version: major '{0', minor '{1}'", _version.major, _version.minor);
			return;
		}
		m_version = _version;
	}



	template <http_body T>
	auto basic_http_message<T>::getHttpVersion() const noexcept -> http_version
	{
		return m_version;
	}



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



	template <http_body T>
	auto basic_http_message<T>::prepare() noexcept -> void
	{
		emplaceHeader(http_header::content_lenth, 0);
	}



	template <http_body T>
	auto basic_http_message<T>::build() const -> std::string
	{
		std::stringstream builded_message(buildStartLine());

		for (const auto& [key, value] : m_headers)
		{
			builded_message << key << ": " << value << "\r\n";
		}
		builded_message << "\r\n";

		builded_message << static_cast<std::string>(m_body) << "\r\n";
	}
}