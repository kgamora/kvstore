#include <cstdint>
#include <grpcpp/channel.h>
#include <optional>
#include <string>

namespace NKVStore {
class TClient {

  uint64_t port;

public:
  explicit TClient(uint64_t port) noexcept;

  void getCommand(uint64_t key);
  void putCommand(const std::string &value);

private:
  std::optional<std::string> get(uint64_t key);
  uint64_t put(const std::string &value);
  std::shared_ptr<grpc::Channel> getChannel();
};
} // namespace NKVStore
