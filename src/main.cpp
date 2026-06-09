#include "dualstore_decoder.h"
#include "dualstore_encoder.h"
#include <iostream>

using namespace std;

int main() {

  DualStoreEncoder encoder;

  encoder.writeInt(10, 123456789);
  encoder.writeDouble(11, 3.14159);
  encoder.writeBool(12, true);
  encoder.writeString(13, "Hello Dual Store");

  std::vector<uint8_t> result = encoder.getFinishedBytes();

  std::cout << "Total Encoded Bytes: " << result.size() << std::endl;

  // Hex အနေနဲ့ ထုတ်ကြည့်ချင်ရင်
//   for (uint8_t b : result) {
//     printf("%02X ", b);
//   }

  DualStoreDecoder decoder{result, [](const std::string &msg) {
                             cout << "Decode Error: " << msg << endl;
                           }};

  decoder.printDecodedData();
  std::cout << std::endl;

  return 0;
}