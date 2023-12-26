#pragma once

#include <engine/net/http/basic_http_message.hpp>
#include <engine/net/http/url.hpp>

#include <sstream>



namespace engine::net::http
{
	enum class request_method : uint8_t
	{
		Get,
		Post,
		Delete,
		Put,
		Trace
	};



	template <http_body T>
	class request : public basic_http_message<T>
	{
	public:

		request() = default;

		void setMethod(request_method _method) noexcept;
		request_method getMethod() const noexcept;

		void setURL(const url& _url) noexcept;
		void setURL(url&& _url) noexcept;
		const url& getURL() const & noexcept;

	protected:

		std::string buildStartLine() const override;

	private:

		request_method m_method = request_method::Get;

		url m_url = "/";

	};





	std::string toString(request_method _method) noexcept;

	request_method fromString(const std::string& _method_str);



	template <http_body T>
	auto request<T>::setMethod(request_method _method) noexcept -> void
	{
		m_method = _method;
	}



	template <http_body T>
	auto request<T>::getMethod() const noexcept -> request_method
	{
		return m_method;
	}



	template <http_body T>
	auto request<T>::setURL(const url& _url) noexcept -> void
	{
		m_url = _url;
	}



	template <http_body T>
	auto request<T>::setURL(url&& _url) noexcept -> void
	{
		m_url = std::move(_url);
	}



	template <http_body T>
	auto request<T>::getURL() const& noexcept -> const url&
	{
		return m_url;
	}



	template <http_body T>
	auto request<T>::buildStartLine() const -> std::string
	{
		std::stringstream start_line;

		start_line << toString(m_method) << " " << static_cast<std::string>(m_url)
				   << " HTTP/" << static_cast<int>(this->m_version.major) << "." << static_cast<int>(this->m_version.minor);

		return start_line.str();
	}
}