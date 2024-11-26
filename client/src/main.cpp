#include "CLI/CLI.hpp"

#include <cstdint>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  CLI::App app{"kvstore server client"};
  argv = app.ensure_utf8(argv);
  app.require_subcommand(1);

  // client configuration
  app.add_option("--port,-p", "kvstore-server port")
      ->configurable()
      ->required();

  // get command
  uint64_t key;
  auto getCommand = app.add_subcommand("get", "get value by key");
  getCommand->add_option("key", key)->required();
  getCommand->callback(
      [&]() { std::cout << "got get command with key: " << key << std::endl; });

  // put command
  std::string value;
  auto putCommand = app.add_subcommand("put", "put value and get its key");
  putCommand->add_option("value", value)->required();
  putCommand->callback([&]() {
    std::cout << "got put command with value: " << value << std::endl;
  });

  CLI11_PARSE(app, argc, argv);
}
