#pragma once

#include "avl_tree.hpp"
#include "common.hpp"

#include <cstddef>
#include <memory>
namespace keyvaluestorage::core {

class TMemtable {
  std::size_t Size;
  core::AVLTree<TKey, TValue> KeyValue;

public:
  std::size_t GetSize() { return Size; }
  TKey Put() {
    // Size -= size(currentValue)
    // auto it = KeyValue.insert_or_assign({}, {});
    // Size += size(newValue)
    // return it.first;
  };
};

using TMemtablePtr = std::unique_ptr<TMemtable>;

} // namespace keyvaluestorage::core
