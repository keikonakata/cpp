#include <cassert>
#include "dfs_norec.hpp"

template<typename T>
void check(typename DfsNorec<T>::graph_t const& g){
  DfsNorec dfs (g);
  std::unordered_map<T, size_t> m;

  size_t index = 0;
  for (const auto& n : dfs.nodes){
    m.emplace(n, index++);
  }

  for (const auto& edges : g){
    const auto src = edges.first;
    for (const auto trg : edges.second) {
      if (src != trg)
	assert(m.at(trg) < m.at(src));
    }
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  using node_t = int;
  DfsNorec<node_t>::graph_t g;

  uint8_t const len = data[0];
  if (len != 0) {
    std::size_t pos = 0; // std::size_t and size_t are the same
    std::vector<std::vector<node_t>> vv {len};
    for (std::size_t i = 1; i < size; i++) {
      node_t v = data[i] % (pos + 1);
      vv.at(pos).push_back(v);
      pos = pos % len;
    }

    g.emplace(0, std::vector<node_t>());
    for (uint8_t i = 0; i < len; i++){
      g.emplace(i+1, std::move(vv.at(i)));
    }
  }

  check<int>(g);

  return 0;
}
