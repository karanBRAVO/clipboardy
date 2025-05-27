#include <iostream>
#include <memory>

#include "clipboard_manager.hpp"
#include "websocket_client.hpp"

int main(int argc, char** argv) {
  // Check command line arguments.
  if (argc != 3) {
    std::cerr << "Usage: websocket-client <host> <port>\n"
              << "Example:\n"
              << "    websocket-client 127.0.0.1 8080\n";
    return EXIT_FAILURE;
  }
  auto const host = argv[1];
  auto const port = argv[2];

  // The io_context is required for all I/O
  net::io_context ioc;

  // Create clipboard manager
  ClipboardManager clipboard_manager;

  // Create shared client instance
  auto client = std::make_shared<WebSocketClient>(ioc);

  // Listeners
  client->on_connect([]() { std::cout << "[cb] Connected" << std::endl; });
  client->on_disconnect([]() { std::cout << "[cb] Disconnected" << std::endl; });
  client->on_error(
      [](const std::string& error) { std::cout << "[cb] Error" << error << std::endl; });
  client->on_write([]() { std::cout << "[cb] Write successful" << std::endl; });
  client->on_message([&clipboard_manager](const std::string& message) {
    std::cout << "[cb] Received message: " << message << std::endl;
    clipboard_manager.set_text(message);
  });

  // Connect to the server
  client->connect(host, port);

  // Poll the clipboard for changes
  clipboard_manager.poll([&client](const std::string& text) { client->send_message(text); });

  // Run the I/O service. The call will return when
  // the socket is closed.
  ioc.run();

  return EXIT_SUCCESS;
}