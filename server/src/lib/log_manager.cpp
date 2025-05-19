#include "log_manager.hpp"

#include "log.hpp"

#include <format>

namespace keyvaluestorage::core::log {

namespace {

class TLogManager final : public ILogManager {
  const std::string LogFilesPath;
  TVersion CurrentVersion;
public:
  // Dumps memtable into a new log entry
  void Dump(const TMemtablePtr & memtable) const override {
    CurrentVersion++;
    DumpMemtable(memtable);
  };

  // Returns all logs
  std::vector<TLogPtr> GetLogs() const override {
    return {};
  };

  // Merges two logs into a new log entry
  void Merge(TVersion, TVersion) const override {

  };

private:

  void DumpMemtable(const TMemtablePtr & memtable) {
    auto keysFilePath = std::format("{}/{}.{}", LogFilesPath, CurrentVersion, "keys");
    auto valuesFilePath = std::format("{}/{}.{}", LogFilesPath, CurrentVersion, "values");
    auto writer = CreateLogWriter(keysFilePath, valuesFilePath, memtable);
    writer.DumpLog();
  }
};

}

} // namespace keyvaluestorage::core::log
