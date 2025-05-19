#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace keyvaluestorage {

using TKey = uint64_t;
using TValue = std::string;
using TValuePtr = std::unique_ptr<TValue>;
using TPath = std::string;

} // namespace keyvaluestorage
