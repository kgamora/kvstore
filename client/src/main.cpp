#include "CLI/CLI.hpp"

#include "lib/app.hpp"

#include <cstdint>

int main(int argc, char *argv[]) {
  CLI::App app{"kvstore server client"};
  argv = app.ensure_utf8(argv);
  app.require_subcommand(1);

  // client configuration
  uint64_t port;
  app.add_option("--port,-p", port)->configurable()->required();

  // get command
  uint64_t key;
  auto getCommand = app.add_subcommand("get", "get value by key");
  getCommand->add_option("key", key)->required();
  getCommand->callback([&]() { NKVStore::TClient{port}.getCommand(key); });

  // put command
  std::string value;
  auto putCommand = app.add_subcommand("put", "put value and get its key");
  putCommand->add_option("value", value)->required();
  putCommand->callback([&]() { NKVStore::TClient{port}.putCommand(value); });

  CLI11_PARSE(app, argc, argv);
}
