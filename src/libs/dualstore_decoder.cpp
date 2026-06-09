#include "dualstore_decoder.h"
#include "dualstore_encoder.h"
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <variant>

DualStoreDecoder::DualStoreDecoder(
    const std::vector<uint8_t> &inputData,
    std::function<void(const std::string &)> onError)
    : data(inputData), onErrorCallback(onError) {
  decodeAll();
}

void DualStoreDecoder::decodeAll() {
  try {
    while (offset < data.size()) {
      if (offset >= data.size())
        throw std::out_of_range("Incomplete data: Missing key");
      // key
      uint8_t key = data[offset++];
      if (offset >= data.size())
        throw std::out_of_range("Incomplete data: Missing Type");
      uint8_t type = data[offset++];

      if (type == DualStoreEncoder::TYPE_INT) {
        if (offset + 8 > data.size())
          throw std::out_of_range("Incomplete data for Int64");
        int64_t val;
        std::memcpy(&val, &data[offset], 8);
        offset += 8;
        decodedValue[type] = val;

      } else if (type == DualStoreEncoder::TYPE_BOOL) {
        if (offset >= data.size())
          throw std::out_of_range("Incomplete data for Bool");
        bool val = (data[offset++] == 1);
        decodedValue[type] = val;

      } else if (type == DualStoreEncoder::TYPE_DOUBLE) {
        if (offset + 8 > data.size())
          throw std::out_of_range("Incomplete data for Double");
        double val;
        std::memcpy(&val, &data[offset], 8);
        offset += 8;
        decodedValue[type] = val;

      } else if (type == DualStoreEncoder::TYPE_STRING) {
        if (offset + 4 > data.size())
          throw std::out_of_range("Incomplete data for String length");
        int32_t strLen;
        std::memcpy(&strLen, &data[offset], 4);
        offset += 4;

        if ((offset + strLen) > data.size())
          throw std::out_of_range("Incomplete data for String Value");
        std::string val(data.begin() + offset, data.begin() + offset + strLen);
        offset += strLen;
        decodedValue[type] = val;
      } else {
        std::cout << "Type: " << type << std::endl;
        throw std::runtime_error("Unknown data type marker");
      }
    }
  } catch (const std::exception &e) {
    if (onErrorCallback) {
      onErrorCallback(e.what());
    }
  }
}

const std::unordered_map<uint8_t, DualStoreDecoder::EncodedValue>
DualStoreDecoder::getDecodedData() const {
  return getDecodedData();
}

int64_t DualStoreDecoder::getInt(uint8_t key, int64_t defVal) const {
  auto it = decodedValue.find(key);
  if (it != decodedValue.end() && std::holds_alternative<int64_t>(it->second)) {
    return std::get<int64_t>(it->second);
  }
  return defVal;
}

double DualStoreDecoder::getDouble(uint8_t key, double defVal) const {
  auto it = decodedValue.find(key);
  if (it != decodedValue.end() && std::holds_alternative<double>(it->second)) {
    return std::get<double>(it->second);
  }
  return defVal;
}
bool DualStoreDecoder::getBool(uint8_t key, bool defVal) const {
  auto it = decodedValue.find(key);
  if (it != decodedValue.end() && std::holds_alternative<bool>(it->second)) {
    return std::get<bool>(it->second);
  }
  return defVal;
}
std::string DualStoreDecoder::getString(uint8_t key,
                                        const std::string &defVal) const {
  auto it = decodedValue.find(key);
  if (it != decodedValue.end() &&
      std::holds_alternative<std::string>(it->second)) {
    return std::get<std::string>(it->second);
  }
  return defVal;
}

void DualStoreDecoder::printDecodedData() {
  std::cout << "Map: {" << "\n";
  for (const auto &[k, v] : decodedValue) {
    std::cout << "Key: " << (int)k;
    std::visit([](const auto arg) { std::cout <<" Val: " << arg; }, v);
    std::cout << "\n";
  }
  std::cout << "}" << "\n";
}