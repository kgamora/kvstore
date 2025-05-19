#include "service.hpp"

#include "common.hpp"
#include "log_service.hpp"
#include <algorithm>
#include <memory>
#include <optional>

namespace keyvaluestorage {

namespace {

using namespace core::log;

class TKeyValueStorageService final : public IKeyValueStorageService {
  TKey MaxCurrentKey;
  TMemtable Memtable;
  TLogServicePtr LogService;

  TKey PutImpl(std::optional<TKey> key, TValuePtr value) {
    // TODO: move?
    if (!key) {
      key = ++MaxCurrentKey;
    }
    auto it = Memtable.insert_or_assign(*key, *value);
    return *key;
  }

public:
  TKeyValueStorageService(TLogServicePtr logService, TMemtable memtable,
                          TKey maxCurrentKey)
      : LogService(std::move(logService)), Memtable(std::move(memtable)),
        MaxCurrentKey(maxCurrentKey) {};

  void Put(TKey key, TValuePtr value) override {
    PutImpl(std::make_optional(key), std::move(value));
  };

  TKey Put(TValuePtr value) override {
    return PutImpl(std::nullopt, std::move(value));
  };

  TValuePtr Get(TKey key) const override {
    auto it = Memtable.find(key);
    if (it != Memtable.end()) {
      return std::make_unique<TValue>(*it->value);
    }
    return LogService->Get(key);
  };
};

} // namespace

TKeyValueStorageServicePtr CreateKeyValueStorageService() {
  return std::make_unique<TKeyValueStorageService>();
}

} // namespace keyvaluestorage
