#include "kvstore/keyvaluestorage.pb.h"
#include <cstdint>
#include <grpcpp/support/status.h>
#include <kvstore/keyvalue.pb.h>
#include <kvstore/keyvaluestorage.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include <string>
#include <unordered_map>

namespace keyvaluestorage {

class KeyValueStorageService final : public KeyValueStorage::Service {

  virtual grpc::Status Put(grpc::ServerContext *context,
                           const PutRequest *request,
                           PutResponse *response) override {
    storage.insert_or_assign(counter, request->value().data());

    response->mutable_key()->set_key(counter++);
    response->set_success(true);

    return grpc::Status::OK;
  }

  virtual grpc::Status Get(grpc::ServerContext *context,
                           const GetRequest *request,
                           GetResponse *response) override {
    auto key = request->key().key();
    auto it = storage.find(key);
    bool present = it != storage.end();

    if (present) {
      response->mutable_value()->set_data(it->second);
    }

    response->set_present(present);

    return grpc::Status::OK;
  }

private:
  std::uint64_t counter;
  std::unordered_map<std::uint64_t, std::string> storage;
};

} // namespace keyvaluestorage

int main() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

  keyvaluestorage::KeyValueStorageService my_service{};
  builder.RegisterService(&my_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();

  return 0;
}
