#include "dualstore_encoder.h"
#include <cstdint>
#include <cstring>

void DualStoreEncoder::writeKey(uint8_t key) { buffer.push_back(key); }

const std::vector<uint8_t> DualStoreEncoder::getFinishedBytes() const {
  return buffer;
}

void DualStoreEncoder::writeInt(uint8_t key, int64_t value) {
  writeKey(key);
  buffer.push_back(DualStoreEncoder::TYPE_INT);

  int byte_len = 8;
  uint8_t bytes[byte_len];
  std::memcpy(bytes, &value, sizeof(value));
  buffer.insert(buffer.end(), bytes, bytes + byte_len);
}

void DualStoreEncoder::writeDouble(uint8_t key, double value) {
  writeKey(key);
  buffer.push_back(DualStoreEncoder::TYPE_DOUBLE);

  uint8_t bytes[8];
  std::memcpy(bytes, &value, sizeof(value));
  buffer.insert(buffer.end(), bytes, bytes + 8);
}
void DualStoreEncoder::writeBool(uint8_t key, bool value) {
  writeKey(key);
  buffer.push_back(DualStoreEncoder::TYPE_BOOL);
  buffer.push_back(value ? 1 : 0);
}
void DualStoreEncoder::writeString(uint8_t key, const std::string &value) {
  writeKey(key);
  buffer.push_back(DualStoreEncoder::TYPE_STRING);

  int32_t strLen = static_cast<int32_t>(value.length());
  uint8_t lenBytes[4];
  std::memcpy(lenBytes, &strLen, sizeof(strLen));
  buffer.insert(buffer.end(), lenBytes, lenBytes + 4);
  //   set value
  buffer.insert(buffer.end(), value.begin(), value.end());
}