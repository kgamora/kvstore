#pragma once

#include "common.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace keyvaluestorage::core::log {

struct TKeyLogEntry {
  TKey Key;
  size_t Position;
  size_t Size;
};

using TVersion = uint32_t;

class ILog {
public:
  virtual TVersion GetVersion() const = 0;
  virtual TValuePtr Get(const TKey &) const = 0;
};

using TLogPtr = std::unique_ptr<const ILog>;

class ILogWriter {
  virtual void DumpLog() const = 0;
}

class ILogReader {
  virtual std::vector<TKey> ReadKeys() const = 0;
  virtual TValuePtr ReadValue(size_t i) const = 0;
}

using TLogWriterPtr = std::unique_ptr<const ILogWriter>;
using TLogReaderPtr = std::unique_ptr<const ILogReader>;

TLogWriterPtr CreateLogWriter(std::string keysFilePath, std::string valuesFilePath, const TMemtablePtr & memtable);
TLogWriterPtr CreateLogReader(std::string keysFilePath, std::string valuesFilePath);

} // namespace keyvaluestorage::core::log
