#pragma once

#include <engine/net/http/http_server.hpp>

#include <memory>



namespace auth
{
	using namespace engine::net;

	class authorization_server : protected http::http_server
	{
	public:

		authorization_server() noexcept;
		~authorization_server();

		bool startOn(std::string_view _address, uint16_t _port = 80);

	private:

		bool connectToDataBase() noexcept;

		void registrateAPI() noexcept;

		// API - POST - '/api/v1/users' 
		http::response_t createUserHandler(http::request_t& _request) noexcept;

	private:

		class authorization_server_impl;

		using pimpl_ptr_t = std::unique_ptr<authorization_server_impl>;

		const pimpl_ptr_t& pimpl() const noexcept;

	private:

		pimpl_ptr_t m_pimpl = nullptr;

	};
}