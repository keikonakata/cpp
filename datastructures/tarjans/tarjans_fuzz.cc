#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "tarjans.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  using namespace tarjans;

  graph_t g;

  uint8_t const len = data[0];
  if (len != 0) {
    std::size_t pos = 0; // std::size_t and size_t are the same
    std::vector<std::vector<vertex_t>> vv {len};
    for (std::size_t i = 1; i < size; i++) {
      vertex_t v = data[i] % len;
      vv.at(pos).push_back(v);
      pos = (pos + 1) % len;
    }

    for (uint8_t i = 0; i < len; i++){
      g.insert(std::pair{i, std::move(vv.at(i))});
    }
  }

  Tarjans t (g);
  return 0;
}
