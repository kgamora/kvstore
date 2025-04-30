#pragma once

#include "common.hpp"

#include <memory>

namespace keyvaluestorage {

class IKeyValueStorageService {
public:
  virtual TKey Put(TValuePtr) = 0;
  virtual void Put(TKey, TValuePtr) = 0;
  virtual TValuePtr Get(TKey) const = 0;
};

using TKeyValueStorageServicePtr = std::unique_ptr<IKeyValueStorageService>;

} // namespace keyvaluestorage
