#pragma once

#include "common.hpp"
#include <memory>

namespace keyvaluestorage::core::log {

class ILogService {
public:
  virtual TValuePtr Get(const TKey &) const = 0;
  virtual void Dump(const TMemtable &) const = 0;
};

using TLogServicePtr = std::unique_ptr<const ILogService>;

struct TLogServiceConfig {};

using TLogServiceConfigPtr = std::unique_ptr<const TLogServiceConfig>;

TLogServicePtr CreateLogService(TLogServiceConfigPtr config);
} // namespace keyvaluestorage::core::log
