#ifndef TARJANS_H_INCLUDED
#define TARJANS_H_INCLUDED

#include <exception>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

namespace tarjans {
  using vertex_t = int;
  using index_t = std::size_t;

  using graph_t = std::unordered_map<vertex_t, std::vector<vertex_t>>;
  using indexes_t = std::unordered_map<vertex_t, index_t>;
  using component_t = std::vector<vertex_t>;
  using components_t = std::vector<component_t>;
  // use map (instead of unordered_map) due to range access
  // (Does it really perform better?)
  using stack_t = std::map<index_t, vertex_t>;

  class Tarjans {
  public:
    components_t components;
    // requires \dom(graph) is the set of vertexes
    Tarjans(const graph_t&);
  private:
    const graph_t& graph;
    indexes_t indexes;
    stack_t stack;
    index_t next_index {0};

    index_t tarjans_rec(vertex_t, const std::vector<vertex_t>&);
  };
}

#endif /* TARJANS_H_INCLUDED */
