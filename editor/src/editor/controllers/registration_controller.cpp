#include <editor/controllers/registration_controller.hpp>

#include <engine/Engine.hpp>

#include <auth/authorization_client.hpp>

#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>



namespace editor::controllers
{
	auto registration_controller::onClickRegistrateButton(const auth::user& _user) noexcept -> asio::awaitable<engine::error::error> try
	{
		auth::authorization_client client(engine::Engine::getApplicationExecutor()->IOContext(),
										  engine::net::http::host("127.0.0.1", 80));

		auto error = co_await client.registrateUser(_user);

		co_return error;
	}
	catch (const std::exception& _ex)
	{
		LOG_ERROR("Exception: {0}", std::string(_ex.what()));
		throw;
	}
}