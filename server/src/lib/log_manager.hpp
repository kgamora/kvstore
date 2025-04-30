#pragma once

#include "common.hpp"
#include "log.hpp"
#include <memory>
#include <vector>

namespace keyvaluestorage::core::log {

class ILogManager {
public:
  // Dumps memtable into a new log entry
  virtual void Dump(const TMemtable &) const = 0;
  // Returns all logs
  virtual std::vector<ILogPtr> GetLogs() const = 0;
  // Merges two logs into a new log entry
  virtual void Merge(log::TVersion, log::TVersion) const = 0;
};

using TLogManagerPtr = std::unique_ptr<const ILogManager>;

} // namespace keyvaluestorage::core::log
