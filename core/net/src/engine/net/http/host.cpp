#include <engine/net/http/host.hpp>

#include <engine/net/net.hpp>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>





using namespace asio::ip;

namespace engine::net::http
{
	class host::host_pimpl
	{
	public:

		host_pimpl() = default;
		host_pimpl(std::string_view _host, uint16_t _port);
		~host_pimpl() = default;

		void setAddress(std::string_view _address);
		void setPort(uint16_t _port);

		std::string getAddress() const;
		uint16_t getPort() const;

	private:

		tcp::endpoint resolveHostname(std::string_view _hostname, uint16_t _port);

	private:

		tcp::endpoint m_host_endpoint;

	};



	host::host_pimpl::host_pimpl(std::string_view _host, uint16_t _port)
	{ 
		address host_address;
		asio::error_code error;
		host_address = make_address(_host, error);
		if (error)
			m_host_endpoint = resolveHostname(_host, _port);
		else
			m_host_endpoint = tcp::endpoint(host_address, _port);
	}



	auto host::host_pimpl::resolveHostname(std::string_view _hostname, uint16_t _port) -> tcp::endpoint
	{
		asio::io_context context;
		tcp::resolver resolver(context);
		tcp::resolver::query query(_hostname.data(), std::to_string(_port));
		auto iter = resolver.resolve(query);
		return iter->endpoint();
	}


	auto host::host_pimpl::setAddress(std::string_view _address) -> void
	{
		m_host_endpoint.address(address::from_string(_address.data()));
	}



	auto host::host_pimpl::setPort(uint16_t _port) -> void
	{
		m_host_endpoint.port(_port);
	}



	auto host::host_pimpl::getAddress() const -> std::string
	{
		return m_host_endpoint.address().to_string();
	}



	auto host::host_pimpl::getPort() const -> uint16_t
	{
		return m_host_endpoint.port();
	}





	host::host()
		: m_pimpl(std::make_unique<host_pimpl>())
	{ }



	host::host(std::string_view _host, uint16_t _port)
			: m_pimpl(std::make_unique<host_pimpl>(_host, _port))
	{ }



	auto host::setAddress(std::string_view _address) -> void
	{
		m_pimpl->setAddress(_address);
	}



	auto host::setPort(uint16_t _port) -> void
	{
		m_pimpl->setPort(_port);
	}



	auto host::getAddress() const -> std::string
	{
		return m_pimpl->getAddress();
	}



	auto host::getPort() const -> uint16_t
	{
		return m_pimpl->getPort();
	}



	host::~host()
	{ }
}