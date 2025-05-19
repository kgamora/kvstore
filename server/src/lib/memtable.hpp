#pragma once

#include "avl_tree.hpp"
#include "common.hpp"

#include <cstddef>
#include <memory>
namespace keyvaluestorage::core {

namespace {
class TMemtable {
  std::size_t MaxSize;
  std::size_t Size;
  core::AVLTree<TKey, TValue> KeyValue;

public:
  explicit TMemtable(std::size_t maxSize)
      : MaxSize(maxSize), Size(0UL), KeyValue() {}

  bool IsFull() { return Size >= MaxSize; }
  TKey Put() {
    // Size -= size(currentValue)
    // auto it = KeyValue.insert_or_assign({}, {});
    // Size += size(newValue)
    // return it.first;
  };
};
} // namespace

using TMemtablePtr = std::unique_ptr<TMemtable>;

struct TMemtableConfig {
  std::size_t MaxSize;
};

using TMemtableConfigPtr = std::unique_ptr<const TMemtableConfig>;

TMemtablePtr CreateMemtable(const TMemtableConfigPtr &config) {
  return std::make_unique<TMemtable>(config->MaxSize);
}

} // namespace keyvaluestorage::core
