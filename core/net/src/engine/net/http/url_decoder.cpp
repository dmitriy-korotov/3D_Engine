#include <engine/net/http/url_decoder.hpp>



namespace engine::net::http
{
	auto url_decoder::decode(const std::string& _url) noexcept -> std::string
	{
		std::string decoded_url;
		decoded_url.reserve(_url.size());
		for (size_t i = 0; i < _url.size(); i++)
		{
			if (i + 2 < _url.size() && _url[i] == '%' && _url[i + 1] == '2' && _url[i + 2] == '0')
			{
				decoded_url.push_back(' ');
				i += 2;
				continue;
			}
			decoded_url.push_back(_url[i]);
		}
		return decoded_url;
	}
}