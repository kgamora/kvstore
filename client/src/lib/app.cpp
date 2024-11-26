#include "app.hpp"
#include "kvstore/keyvaluestorage.grpc.pb.h"
#include "kvstore/keyvaluestorage.pb.h"
#include <cstdint>
#include <format>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <memory>
#include <optional>
#include <stdexcept>

namespace NKVStore {

TClient::TClient(uint64_t port) noexcept : port(port) {}

void TClient::getCommand(uint64_t key) {
  auto result = this->get(key);

  if (result->empty()) {
    std::cout << std::format("There's no value with key {} in storage", key)
              << std::endl;
    return;
  }

  std::cout << result.value() << std::endl;
}
void TClient::putCommand(const std::string &value) {
  auto result = this->put(value);
  std::cout << result << std::endl;
}

std::shared_ptr<grpc::Channel> TClient::getChannel() {
  auto address = std::format("localhost:{}", port);
  return std::move(
      grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));
}

std::optional<std::string> TClient::get(uint64_t key) {
  using namespace keyvaluestorage;
  GetRequest request;
  GetResponse response;
  request.mutable_key()->set_key(key);

  auto channel = this->getChannel();
  std::unique_ptr<KeyValueStorage::Stub> stub =
      KeyValueStorage::NewStub(channel);
  grpc::ClientContext context;
  grpc::Status status = stub->Get(&context, request, &response);

  if (!status.ok()) {
    auto errorMessage =
        std::format("Get request ended with error with message: \"{}\"",
                    status.error_message());
    throw std::runtime_error(errorMessage);
  }

  return response.present()
             ? std::make_optional(std::move(response.value().data()))
             : std::nullopt;
};

uint64_t TClient::put(const std::string &value) {
  using namespace keyvaluestorage;
  PutRequest request;
  PutResponse response;
  request.mutable_value()->set_data(value);

  auto channel = this->getChannel();
  std::unique_ptr<KeyValueStorage::Stub> stub =
      KeyValueStorage::NewStub(channel);
  grpc::ClientContext context;
  grpc::Status status = stub->Put(&context, request, &response);

  if (!status.ok()) {
    auto errorMessage =
        std::format("Put request ended with error with message: \"{}\"",
                    status.error_message());
    throw std::runtime_error(errorMessage);
  }

  if (!response.success()) {
    throw std::runtime_error("Put request was not successful");
  }

  return response.key().key();
};

} // namespace NKVStore
