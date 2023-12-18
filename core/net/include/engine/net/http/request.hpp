#pragma once

#include <engine/net/http/basic_http_message.hpp>

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

		void setURL(const std::string& _url) noexcept;
		void setURL(std::string&& _url) noexcept;
		const std::string& getURL() const & noexcept;

	protected:

		std::string buildStartLine() const override;

	private:

		request_method m_method = request_method::Get;

		std::string m_url = "/";

	};





	std::string toString(request_method _method) noexcept;



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
	auto request<T>::setURL(const std::string& _url) noexcept -> void
	{
		m_url = _url;
	}



	template <http_body T>
	auto request<T>::setURL(std::string&& _url) noexcept -> void
	{
		m_url = std::move(_url);
	}



	template <http_body T>
	auto request<T>::getURL() const& noexcept -> const std::string&
	{
		return m_url;
	}



	template <http_body T>
	auto request<T>::buildStartLine() const -> std::string
	{
		std::stringstream start_line;

		start_line << toString(m_method) << " " << m_url
				   << " HTTP/" << static_cast<int>(this->m_version.major) << "." << static_cast<int>(this->m_version.minor);

		return start_line.str();
	}
}