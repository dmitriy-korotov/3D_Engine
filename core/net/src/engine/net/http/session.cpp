#include <engine/net/http/session.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/date.hpp>
#include <engine/util/file_reader.hpp>

#include <engine/net/util/ip.hpp>
#include <engine/net/http/request_parser.hpp>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/buffer.hpp>

#include <ctime>
#include <chrono>
#include <filesystem>



namespace engine::net::http
{
	session::session(tcp_socket_t&& _socket, hcontext_sptr_t _handlers_context) noexcept
			: m_socket(std::move(_socket))
			, m_handlers_context(std::move(_handlers_context))
	{ }



	auto session::start() noexcept -> void
	{
		asio::co_spawn(m_socket.get_executor(), startSession(shared_from_this()), asio::detached);
	}



	auto session::startSession(session_ptr_t _session) noexcept -> asio::awaitable<void> try
	{
		char buffer[BUFFER_SIZE] = {};

		auto bytes_readed = co_await m_socket.async_read_some(asio::buffer(buffer), asio::use_awaitable);
		if (bytes_readed == 0)
			LOG_WARN("[Http session WARN] recived zero bytes");

		request_parser<string_body> parser;
		parser.parse(buffer);
		auto request = std::move(parser).get();

		LOG_INFO("[Http session INFO] {0}: url '{1}'", utility::toString(m_socket.remote_endpoint()), request.getURL());

		auto response = handleRequest(request);
		auto bytes_sended = co_await m_socket.async_write_some(asio::buffer(response.build()), asio::use_awaitable);
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("[Http session ERROR] Cached exception: '{0}'", std::string(_ex.what()));
	}



	auto session::handleRequest(const request<string_body>& _request) noexcept -> response<string_body>
	{
		response<string_body> response;
		auto url = _request.getURL();
		const auto& handler = m_handlers_context->handlers.find(url);
		if (handler != m_handlers_context->handlers.end())
		{
			response = std::invoke(handler->second, _request);
		}
		else
		{
			auto absolute_path = m_handlers_context->work_directory / url.substr(1, url.size() - 1);
			if (std::filesystem::exists(absolute_path))
			{
				if (absolute_path.extension() == ".png")
					response.emplaceHeader(http_header::content_type, "image/png");
				util::file_reader reader(absolute_path);
				response.setBody(std::move(reader.getData()));
			}
			else
			{
				response.setStatus(response_status::not_found);
				response.setBody("<html><h1>Not found</h1></html>");
			}
		}

		response.emplaceHeader(http_header::date, util::toString(util::GetTimeNow()));
		response.emplaceHeader(http_header::host, "Engine");

		return response;
	}
}