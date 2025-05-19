#include "log_service.hpp"

#include "log_manager.hpp"

namespace keyvaluestorage::core::log {

class TLogService final : ILogService {
  TLogManagerPtr LogManager;

public:
  TValuePtr Get(const TKey &key) const override {
    auto logs = LogManager->GetLogs();
    for (auto &log : logs) {
      if (auto value = log->Get(key); value) {
        return value;
      }
    }

    return {};
  };

  void Dump(TMemtablePtr memtable) const override {
    LogManager->Dump(memtable);
  };
};

} // namespace keyvaluestorage::core::log
