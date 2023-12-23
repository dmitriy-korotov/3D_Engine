#pragma once

#include <engine/net/http/request.hpp>
#include <engine/net/http/response.hpp>
#include <engine/net/http/string_body.hpp>

#include <functional>
#include <filesystem>
#include <memory>



namespace engine::net::http
{
	using std::filesystem::path;

	using url_handler_t = std::function<response<string_body>(const request<string_body>&)>;

	class handlers_context
	{
	public:

		path work_directory;
		std::unordered_map<std::string, url_handler_t> handlers;

	};

	using hcontext_sptr_t = std::shared_ptr<handlers_context>;
}