#include "service.hpp"

#include "common.hpp"
#include "log_service.hpp"
#include "memtable.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <utility>

namespace keyvaluestorage {

using namespace core;
using namespace log;

using TMemtableProvider = std::function<TMemtablePtr()>;

namespace {

class TKeyValueStorageService final : public IKeyValueStorageService {
  const TLogServicePtr LogService;
  const TMemtableProvider MemtableProvider;
  TMemtablePtr Memtable;
  TKey MaxCurrentKey;

  TKey PutImpl(std::optional<TKey> key, TValuePtr value) {
    if (Memtable->IsFull()) {
      LogService->Dump(std::move(Memtable));
      Memtable = MemtableProvider();
    }
    // TODO: move?
    if (!key) {
      key = ++MaxCurrentKey;
    }
    auto it = Memtable->insert_or_assign(*key, *value);
    return *key;
  }

public:
  TKeyValueStorageService(TLogServicePtr logService,
                          TMemtableProvider memtableProvider,
                          TKey maxCurrentKey = 0UL)
      : LogService(std::move(logService)),
        MemtableProvider(std::move(memtableProvider)),
        Memtable(MemtableProvider()), MaxCurrentKey(maxCurrentKey) {};

  void Put(TKey key, TValuePtr value) override {
    PutImpl(std::make_optional(key), std::move(value));
  };

  TKey Put(TValuePtr value) override {
    return PutImpl(std::nullopt, std::move(value));
  };

  TValuePtr Get(TKey key) const override {
    auto it = Memtable->find(key);
    if (it != Memtable->end()) {
      return std::make_unique<TValue>(*it->value);
    }
    return LogService->Get(key);
  };
};

} // namespace

auto CreateKeyValueStorageService(TKeyValueStorageServiceConfigPtr config,
                                  TMemtableProvider memtableProvider,
                                  TLogServicePtr logService)
    -> TKeyValueStorageServicePtr {
  std::ignore = config;
  return std::make_unique<TKeyValueStorageService>(std::move(logService),
                                                   std::move(memtableProvider));
}

} // namespace keyvaluestorage
