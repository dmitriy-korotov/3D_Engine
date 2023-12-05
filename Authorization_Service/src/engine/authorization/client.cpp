#include <engine/authorization/client.hpp>



namespace engine::authorization
{
	client::client(std::string_view _address, uint16_t _port)
			: m_socket(m_excution_cxt)
	{ }



	bool client::connectTo(std::string_view _address, uint16_t _port)
	{
		//m_socket.async_connect()
		return true;
	}
}