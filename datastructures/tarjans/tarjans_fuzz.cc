#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "tarjans.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  using namespace tarjans;

  graph_t const g;

    uint8_t const len = data[0] + static_cast<uint8_t>(1);
    std::size_t pos = 0; // std::size_t and size_t are the same
    std::vector<std::vector<uint8_t>> vv {len};
    for (std::size_t i = 1; i < len ; i++) {
      vv.at(pos).emplace_back(i);
      pos = (pos + 1) % len;
    }

  Tarjans t (g);
  return 0;
}
