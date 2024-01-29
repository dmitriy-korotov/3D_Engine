#include <editor/controllers/registration_controller.hpp>

#include <auth/authorization_client.hpp>

#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>





static auto wrapper(auth::authorization_client& _client, const auth::user& _user) -> asio::awaitable<void>
{
	try
	{
		auto error = co_await _client.registrateUser(_user);
		if (error)
			LOG_ERROR("[Authorization controller ERROR] Code: '{0}'; Message: '{1}'", error.code(), error.message());
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("[Authorization controller ERROR] Exception: '{0}'", std::string(_ex.what()));
	}
}





namespace editor::controllers
{
	auto registration_controller::registrateUser(const auth::user& _user) noexcept -> bool
	{
		asio::io_context context;
		auth::authorization_client client(context);

		client.connect(engine::net::http::host("127.0.0.1", 80));
		asio::co_spawn(context, wrapper(client, _user), asio::detached);

		context.run();

		client.disconnect();

		return true;
	}
}