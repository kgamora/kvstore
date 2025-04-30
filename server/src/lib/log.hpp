#pragma once

#include "common.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace keyvaluestorage::core::log {

using TVersion = uint32_t;

class ILog {
public:
  virtual TVersion GetVersion() const = 0;
  virtual TValuePtr Get(const TKey &) const = 0;
  // TODO: normal self-docs everywhere
  // Returns sorted key-value pairs. Used for compaction
  virtual std::vector<std::pair<TKey, TValuePtr>> GetItems() const;
};

using ILogPtr = std::unique_ptr<const ILog>;

} // namespace keyvaluestorage::core::log
