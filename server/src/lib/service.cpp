#include "service.hpp"

#include "common.hpp"
#include "log_service.hpp"
#include <optional>

namespace keyvaluestorage {

class TKeyValueStorageService final : IKeyValueStorageService {
private:
  TKey MaxCurrentKey;
  TMemtable Memtable;
  core::log::TLogServicePtr LogService;

  TKey PutImpl(std::optional<TKey> key, TValuePtr value) {
    // TODO: move?
    if (!key) {
      key = ++MaxCurrentKey;
    }
    auto it = Memtable.insert_or_assign(*key, *value);
    return *key;
  }

public:
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
} // namespace keyvaluestorage
