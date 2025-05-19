#pragma once

#include "common.hpp"
#include <memory>

namespace keyvaluestorage::core::log {

class ILogService {
public:
  virtual TValuePtr Get(const TKey &) const = 0;
  virtual void Dump(TMemtablePtr) const = 0;
};

using TLogServicePtr = std::unique_ptr<const ILogService>;

} // namespace keyvaluestorage::core::log
