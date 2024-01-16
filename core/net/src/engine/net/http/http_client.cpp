#include <engine/net/http/http_client.hpp>

#include <engine/logging/log.hpp>



namespace engine::net::http
{
	http_client::http_client() noexcept
			: m_socket(m_execution_cxt)
	{ }
	


	auto http_client::getContext() noexcept -> asio::io_context&
	{
		return m_execution_cxt;
	}
}