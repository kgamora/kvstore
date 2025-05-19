#pragma once

#include "avl_tree.hpp"
#include <cstdint>
#include <memory>
#include <string>
namespace keyvaluestorage {
using TKey = uint64_t;
using TValue = std::string;
using TValuePtr = std::unique_ptr<TValue>;
using TPath = std::string;
using TMemtable = core::AVLTree<TKey, TValue>;
using TMemtablePtr = std::unique_ptr<core::AVLTree<TKey, TValue>>;
} // namespace keyvaluestorage
