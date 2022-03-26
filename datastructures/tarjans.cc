// clang++-10 -Wall -std=c++17 tarjans.cc
// bazel build //datastructures:tarjans
#include <exception>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "tarjans.h"

// require vertex notin dom(indexes)
// require (verex |-> targets) in graph
// return the lowest link of vertex
index_t Tarjans::tarjans_rec(vertex_t vertex, const std::vector<vertex_t>& targets){
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
Tarjans::Tarjans(const graph_t& _graph) : graph(_graph) {
  for (auto& single_source_edges : graph){// O(V)
    auto vertex = single_source_edges.first;
    if (auto i = indexes.find(vertex); i == indexes.end()){
      tarjans_rec(vertex, single_source_edges.second);
    }
  }
}
