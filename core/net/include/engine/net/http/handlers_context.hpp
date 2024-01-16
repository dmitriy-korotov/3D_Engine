#pragma once

#include <engine/net/http/request.hpp>
#include <engine/net/http/response.hpp>
#include <engine/net/http/string_body.hpp>

#include <functional>
#include <filesystem>
#include <memory>
#include <mutex>



namespace engine::net::http
{
	using std::filesystem::path;

	using request_t = request<string_body>;
	using response_t = response<string_body>;

	using url_handler_t = std::function<response_t(const request_t&)>;

	using handlers_storage_t = std::unordered_map<request_method, std::unordered_map<std::string, url_handler_t>>;

	class handlers_context
	{
	public:

		path work_directory;
		handlers_storage_t handlers;
		std::mutex handlers_mutex;

	};

	using hcontext_sptr_t = std::shared_ptr<handlers_context>;
}