#pragma once

#include <engine/net/net.hpp>

#include <engine/util/nocopyeble.hpp>

#include <memory>



namespace engine::net::http
{
	using namespace asio::ip;

	class http_server: private util::nocopyeble
	{
	public:

		http_server() noexcept;
		http_server(http_server&&) = default;
		http_server& operator=(http_server&&) = default;
		~http_server();

		void listen(std::string_view _address, uint16_t _port = 80);

	private:
		
		class pimpl;
		using upimpl_t = std::unique_ptr<pimpl>;

		upimpl_t& impl() noexcept;
		const upimpl_t& impl() const noexcept;

		upimpl_t m_pimpl = nullptr;
		
	};
}