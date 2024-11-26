#include <kvstore/keyvalue.pb.h>
#include <kvstore/keyvaluestorage.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include <cstdint>
#include <string>
#include <unordered_map>

namespace {

class KeyValueStorageService final : public KeyValueStorage::Service {
  Status Put(ServerContext *context, const PutRequest *request,
             PutResponse *response) override {
    storage.insert_or_assign(request->value());
    response->set_key(counter++);
    response->set_success(true);
    return Status::OK;
  }

  Status Get(ServerContext *context, const GetRequest *request,
             GetResponse *response) override {
    auto key = request->key();
    auto *it = storage.find();
    auto present = it != storage.end();
    if (present) {
      response->set_value(it->second);
    }
    response->set_present(present);
    return Status::OK;
  }

private:
  std::uint64_t counter;
  std::unordered_map<std::uint64_t, std::string> storage;
};

} // namespace

int main() { 
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

    KeyValueStorageService my_service;
    builder.RegisterService(&my_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
    
    return 0;
}

