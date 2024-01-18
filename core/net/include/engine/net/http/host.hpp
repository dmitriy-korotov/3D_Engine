#pragma once

#include <string>
#include <memory>



namespace engine::net::http
{
	class host
	{
	public:

		host();
		host(std::string_view _host, uint16_t _port);
		~host();

		void setAddress(std::string_view _address);
		void setPort(uint16_t _port);

		std::string getAddress() const;
		uint16_t getPort() const;

	private:

		class host_pimpl;

		std::unique_ptr<host_pimpl> m_pimpl;

	};
}