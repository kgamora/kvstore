#include "log_manager.hpp"

#include "common.hpp"
#include "log.hpp"

#include <cstdio>
#include <memory>
#include <string>

namespace keyvaluestorage::core::log {

namespace {

class TLogManager final : public ILogManager {
  std::string LogFilesPath;
  TVersion CurrentVersion;

public:
  TLogManager(TPath logFilesPath, TVersion startVersion)
      : LogFilesPath(logFilesPath), CurrentVersion(startVersion) {}

  // Dumps memtable into a new log entry
  void Dump(TMemtablePtr memtable) override {
    CurrentVersion++;
    DumpMemtable(std::move(memtable));
  };

  // Returns all logs
  std::vector<TLogPtr> GetLogs() const override {

  };

  // Merges two logs into a new log entry
  void Merge(TVersion, TVersion) const override{

  };

private:
  void DumpMemtable(TMemtablePtr memtable) {
    auto keysFilePath =
        LogFilesPath + '/' + std::to_string(CurrentVersion) + ".keys";
    auto valuesFilePath =
        LogFilesPath + '/' + std::to_string(CurrentVersion) + ".values";
    auto writer =
        CreateLogWriter(keysFilePath, valuesFilePath, std::move(memtable));
    writer->DumpLog();
  }
};

} // namespace

TLogManagerPtr CreateLogManager(TLogManagerConfigPtr config,
                                TVersion startVersion = 0UL) {
  return std::make_unique<TLogManager>(config->LogFilesPath, startVersion);
}

} // namespace keyvaluestorage::core::log
