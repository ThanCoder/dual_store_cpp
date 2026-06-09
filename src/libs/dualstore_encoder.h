#pragma once

#include <cstdint>
#include <string>
#include <vector>

class DualStoreEncoder {

private:
  std::vector<uint8_t> buffer;
  void writeKey(uint8_t key);

public:
  DualStoreEncoder() = default;

  // Value Type Markers
  static constexpr uint8_t TYPE_INT = 1;
  static constexpr uint8_t TYPE_DOUBLE = 2;
  static constexpr uint8_t TYPE_BOOL = 3;
  static constexpr uint8_t TYPE_STRING = 4;

  // method
  void writeInt(uint8_t key, int64_t value);
  void writeDouble(uint8_t key, double value);
  void writeBool(uint8_t key, bool value);
  void writeString(uint8_t key, const std::string &value);

  const std::vector<uint8_t> getFinishedBytes() const;
};