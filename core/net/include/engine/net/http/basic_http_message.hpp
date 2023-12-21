#pragma once

#include <engine/logging/log.hpp>

#include <engine/net/http/fwd/basic_http_message.hpp>

#include <unordered_map>
#include <sstream>
#include <exception>
#include <optional>



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

		using body_wrapp_t = std::decay_t<T>;
		using body_t = typename body_wrapp_t::body_t;
		using headers_t = std::unordered_map<std::string, std::string>;

		basic_http_message() = default;

		void setHttpVersion(http_version _version) noexcept;
		http_version getHttpVersion() const noexcept;

		bool emplaceHeader(std::string _header, std::string _value) noexcept;
		bool emplaceHeader(http_header _key, std::string _value) noexcept;
		void emplaceHeaders(const headers_t& headers) noexcept;

		std::optional<const std::string&> get(std::string_view _header) const noexcept;
		const std::string& at(std::string_view _header) const;

		bool hasBody() const noexcept;

		bool setBody(body_t&& _body) noexcept;
		bool setBody(const body_t& _body) noexcept;
		bool setBody(std::string&& _body) noexcept;
		bool setBody(const std::string& _body) noexcept;

		T&& getBody() &&;
		const T& getBody() const &;

		void prepare() noexcept;

		std::string build() const;

		void reset() noexcept;

	protected:

		virtual std::string buildStartLine() const = 0;

	protected:

		http_version m_version;
		headers_t m_headers;
		std::optional<body_wrapp_t> m_body;

		bool m_is_need_prepare = false;

	};




	std::string toString(http_header _header) noexcept;

	bool isValidHttpVersion(http_version _version) noexcept;



	template <http_body T>
	auto basic_http_message<T>::setHttpVersion(http_version _version) noexcept -> void
	{
		if (!isValidHttpVersion(_version))
		{
			LOG_ERROR("[Basic http message ERROR] Invalid http version: major '{0}', minor '{1}'", _version.major, _version.minor);
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
	auto basic_http_message<T>::emplaceHeaders(const headers_t& headers) noexcept -> void
	{
		for (const auto& [key, value] : headers)
			m_headers.emplace(key, value);
	}




	template <http_body T>
	auto basic_http_message<T>::get(std::string_view _header) const noexcept -> std::optional<const std::string&>
	{
		if (m_headers.contains(_header))
			return m_headers.at(_header);
		return std::nullopt;
	}



	template <http_body T>
	auto basic_http_message<T>::at(std::string_view _header) const -> const std::string&
	{
		return m_headers.at(_header);
	}



	template <http_body T>
	auto basic_http_message<T>::hasBody() const noexcept -> bool
	{
		return m_body.has_value();
	}



	template <http_body T>
	auto basic_http_message<T>::setBody(body_t&& _body) noexcept -> bool
	{
		m_body.emplace(std::move(_body));
		return m_body.value().success();
	}



	template <http_body T>
	auto basic_http_message<T>::setBody(const body_t& _body) noexcept -> bool
	{
		m_body.emplace(_body);
		return m_body.value().success();
	}



	template <http_body T>
	auto basic_http_message<T>::setBody(std::string&& _body) noexcept -> bool
	{
		m_body.emplace(std::in_place, std::move(_body));
		return m_body.value().success();
	}



	template <http_body T>
	auto basic_http_message<T>::setBody(const std::string& _body) noexcept -> bool
	{
		m_body.emplace(std::in_place, _body);
		return m_body.value().success();
	}




	template <http_body T>
	auto basic_http_message<T>::getBody() && -> T&&
	{
		if (!m_body.has_value())
			throw std::runtime_error("Body is empty");
		return std::move(m_body.value());
	}



	template <http_body T>
	auto basic_http_message<T>::getBody() const & -> const T&
	{
		if (!m_body.has_value())
			throw std::runtime_error("Body is empty");
		return m_body.value();
	}



	template <http_body T>
	auto basic_http_message<T>::prepare() noexcept -> void
	{
		m_is_need_prepare = true;
	}



	template <http_body T>
	auto basic_http_message<T>::build() const -> std::string
	{
		std::stringstream builded_message;
		builded_message << buildStartLine() << "\r\n";

		auto body = static_cast<std::string>(m_body.value());

		if (auto content_length_key = toString(http_header::content_lenth); m_is_need_prepare && !m_headers.contains(content_length_key))
			builded_message << content_length_key << ": " << std::to_string(body.size()) << "\r\n";

		for (const auto& [key, value] : m_headers)
			builded_message << key << ": " << value << "\r\n";
		builded_message << "\r\n";

		builded_message << body << "\r\n";

		return builded_message.str();
	}



	template <http_body T>
	auto basic_http_message<T>::reset() noexcept -> void
	{
		m_body.reset();
		m_headers.clear();
		m_is_need_prepare = false;
		m_version = http_version();
	}
}