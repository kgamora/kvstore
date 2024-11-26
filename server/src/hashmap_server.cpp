#include "server.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

namespace {
using TKey = uint64_t;
using TValue = std::string;
} // namespace

namespace NKVS {

class TMapServer : public TKeyValueStorageServer<TKey, TValue> {
public:
  std::optional<TValue> get(TKey key) override {
    if (auto it = storage.find(key); it != storage.end()) {
      return std::make_optional(it->second);
    }

    return {};
  }

  TKey put(std::string value) override {
    storage.emplace(counter++, value);
    return counter;
  }

private:
  TKey counter;
  std::unordered_map<TKey, TValue> storage;
};

} // namespace NKVS
