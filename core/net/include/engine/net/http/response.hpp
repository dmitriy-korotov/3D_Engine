#pragma once

#include <engine/net/http/basic_http_message.hpp>

#include <sstream>



namespace engine::net::http
{
	enum class response_status : uint16_t
	{
		ok = 200,
		not_found = 404,
		forbidden = 403,
		bad_getway = 501,
	};



	template <http_body T>
	class response : public basic_http_message<T>
	{
	public:

		response() = default;

		void setStatus(response_status _status) noexcept;
		response_status getStatus() const noexcept;

	protected:

		std::string buildStartLine() const override;

	private:

		response_status m_status = response_status::ok;

	};





	std::string toString(response_status _status) noexcept;



	template <http_body T>
	auto response<T>::setStatus(response_status _status) noexcept -> void
	{
		m_status = _status;
	}



	template <http_body T>
	auto response<T>::getStatus() const noexcept -> response_status
	{
		return m_status;
	}



	template <http_body T>
	auto response<T>::buildStartLine() const -> std::string
	{
		std::stringstream start_line;

		start_line << "HTTP/" << static_cast<int>(this->m_version.major) << "." << static_cast<int>(this->m_version.minor) << " "
			       << static_cast<uint16_t>(m_status) << " " << toString(m_status) << "\r\n";

		return start_line.str();
	}
}