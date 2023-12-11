#pragma once

#define _WIN32_WINNT 0x0601

#include <asio/ip/tcp.hpp>

using tcp_socket_t = asio::ip::tcp::socket;
using tcp_acceptor_t = asio::ip::tcp::acceptor;