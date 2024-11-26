#pragma once

#include <optional>
namespace NKVS {

template <typename TKey, typename TValue> class TKeyValueStorageServer {
public:
  virtual TKey put(TValue);
  virtual std::optional<TValue> get(TKey);
};

} // namespace NKVS
