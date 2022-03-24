//clang++-10 -Wall -std=c++17 tarjans.cc
#include <exception>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using vertex_t = int;
using index_t = std::size_t;

using graph_t = std::unordered_map<vertex_t, std::vector<vertex_t>>;
using indexes_t = std::unordered_map<vertex_t, index_t>;
using component_t = std::vector<vertex_t>;
using components_t = std::vector<component_t>;
// use map (instead of unordered_map) due to range access
// to increase data locality (is it better?)
using stack_t = std::map<index_t, vertex_t>;
//using stack_t = std::unordered_map<index_t, vertex_t>;

class Tarjans {
public:
  components_t components;
private:
  const graph_t graph;
  indexes_t indexes;
  stack_t stack;
  index_t next_index {0};

  // require vertex notin dom(indexes)
  // require (verex |-> targets) in graph
  // return the lowest link of vertex
  index_t tarjans_rec(vertex_t vertex, const std::vector<vertex_t>& targets){
  auto const my_index = next_index++;
  auto current_lowest_link = my_index;
  indexes.emplace(vertex, my_index);
  stack.emplace(my_index, vertex);
  for (auto const& target : targets) {
    if (auto const target_index = indexes.find(target); target_index == indexes.end()){
      // target is white
      auto const new_edges = graph.find(target);
      if (new_edges == graph.end())
	throw std::invalid_argument("vertex not found in the graph");

      // be aware of possible stack overflow
      auto const lowest_link_child = tarjans_rec(target, new_edges->second);
      if (lowest_link_child < current_lowest_link)
	current_lowest_link = lowest_link_child;
    } else {
      // target is grey or black
      if (stack.find(target_index->second) != stack.end()) {
	// vertex |-> target is a back-edge
	if (target_index->second < current_lowest_link)
	  current_lowest_link = target_index->second;
      }
    }
  }
  if (current_lowest_link == my_index){
    component_t component;
    for (auto i = stack.find(my_index); i != stack.end(); i++) {
      component.emplace_back(i->second);
      stack.erase(i);
    }
    /* for unordered_map stack
   for (auto cur = my_index; cur < next_index; cur++){
      if (auto i = stack.find(cur); i != stack.end()){
	component.emplace_back(i->second);
	stack.erase(i);
      }
    }
    */
    components.emplace_back(std::move(component));
  }
  return current_lowest_link;
}

  // requires \dom(graph) is the set of vertexes
  Tarjans(const graph_t& _graph) : graph(_graph) {
    for (auto& single_source_edges : graph){// O(V)
      auto vertex = single_source_edges.first;
      if (auto i = indexes.find(vertex); i == indexes.end()){
	tarjans_rec(vertex, single_source_edges.second);
      }
    }
  }
};

int main(int argc, char* argv[]){
  return 0;
}
