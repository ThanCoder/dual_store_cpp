#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
class DualStoreDecoder {
public:
  using EncodedValue = std::variant<int64_t, double, bool, std::string>;

private:
  std::vector<uint8_t> data;
  size_t offset = 0;
  std::unordered_map<uint8_t, EncodedValue> decodedValue;
  std::function<void(const std::string &)> onErrorCallback;

  void decodeAll();

public:
  DualStoreDecoder(const std::vector<uint8_t> &inputData,
                   std::function<void(const std::string &)> onError = nullptr);

  const std::unordered_map<uint8_t, EncodedValue> getDecodedData() const;
  int64_t getInt(uint8_t key, int64_t defVal = 0) const;
  double getDouble(uint8_t key, double defVal = 0.0) const;
  bool getBool(uint8_t key, bool defVal = false) const;
  std::string getString(uint8_t key, const std::string &defVal = "") const;

  void printDecodedData();
};