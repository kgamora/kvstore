#include "log.hpp"

#include "memtable.hpp"

namespace keyvaluestorage::core::log {

namespace {

class TLog final : public ILog {
  const std::vector<TKeyLogEntry> Keys;
  const TVersion Version;

public:
  TVersion GetVersion() const override { return Version; }

  TValuePtr Get(const TKey &) const override { return {}; }
};

class TLogWriter final : public ILogWriter {
  const std::string KeysFilePath;
  const std::string ValuesFilePath;
  const TMemtablePtr Memtable;

public:
  TLogWriter(std::string keysFilePath, std::string valuesFilePath,
             TMemtablePtr memtable)
      : KeysFilePath(std::move(keysFilePath)),
        ValuesFilePath(std::move(valuesFilePath)),
        Memtable(std::move(memtable)) {}

  void DumpLog() const override {
    using ios = std::ios;

    auto flags = ios::binary | ios::out | ios::truncate;
    auto logKeysFile = ios::ofstream(KeysFilePath, flags);
    auto logValuesFile = ios::ofstream(ValuesFilePath, flags);

    size_t pos = 0;
    std::vector<TKeyLogEntry> keys;
    for (const auto &[key, value] : *Memtable) {
      logValuesFile.write(value.data(), value.size());
      size_t newPos = logValuesFile.tellp();
      keys.push_back(
          TKeyLogEntry{.Key = key, .Position = pos, .Size = newPos - pos});
      pos = newPos;
    }

    for (auto &key : keys) {
      logKeysFile.write(reinterpret_cast<char *>(&key), sizeof(key));
    }
  }
};

class TLogReader final : public ILogReader {
  const std::string KeysFilePath;
  const std::string ValuesFilePath;

public:
  TLogReader(std::string keysFilePath, std::string valuesFilePath)
      : KeysFilePath(std::move(keysFilePath)),
        ValuesFilePath(std::move(valuesFilePath)) {}
  std::vector<TKey> ReadKeys() const override { return {}; }
  TValuePtr ReadValue(size_t i) const override { return {}; }
};

} // namespace

TLogWriterPtr CreateLogWriter(std::string keysFilePath,
                              std::string valuesFilePath,
                              TMemtablePtr memtable) {
  return std::make_unique<TLogWriter>(
      std::move(keysFilePath), std::move(valuesFilePath), std::move(memtable));
}

TLogReaderPtr CreateLogReader(std::string keysFilePath,
                              std::string valuesFilePath) {
  return std::make_unique<TLogReader>(std::move(keysFilePath),
                                      std::move(valuesFilePath));
}

} // namespace keyvaluestorage::core::log
