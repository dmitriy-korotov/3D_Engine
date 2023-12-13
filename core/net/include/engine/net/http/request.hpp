#pragma once

#include <engine/net/http/basic_http_message.hpp>



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

		setMethod(request_method _method) noexcept;
		request_method getMethod() const noexcept;

	private:

		request_method m_method;

	};
}