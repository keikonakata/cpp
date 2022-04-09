// clang++-10 -Wall -std=c++17 -c tarjans_norec.cc
#include <iterator>
#include "tarjans_norec.h"

using namespace tarjans_norec;

// require vertex notin dom(indexes)
// require (verex |-> targets) in graph
void Tarjans::tarjans_loop(vertex_t root, const std::vector<vertex_t>& targets){
  indexes.emplace(root, next_index);
  lowestlinks.emplace(root, next_index);
  path.insert({next_index, root});
  stack.emplace_back(root, targets.cbegin(), targets.cend());
  ++next_index;

  while (!stack.empty()){
    auto& t = stack.back();
    auto const vertex = std::get<0>(t);
    if (std::get<1>(t) == std::get<2>(t)){
      // the vertex is black
      stack.pop_back();
      auto const index = indexes.at(vertex);
      auto const lowestlink = lowestlinks.at(vertex);
      if (lowestlink == index){
	// the vertex is the root of a SCC
	component_t component;
	for (auto i = path.find(index); i != path.end();) {
	  component.emplace_back(i->second);
	  // i gets invalidated after erase
	  path.erase(i++);
	}
	components.emplace_back(std::move(component));
      }
    } else {
      // the vertex is gray
      vertex_t const target = *std::get<1>(t);
      std::advance(std::get<1>(t), 1);
      if (auto const target_index = indexes.find(target); target_index == indexes.end()){
	// target is white
	auto const new_edges = graph.find(target);
	if (new_edges == graph.end())
	  throw std::invalid_argument("vertex not found in the graph");
	stack.emplace_back(target, new_edges->second.cbegin(), new_edges->second.cend());
      } else {
	// target is grey or black
	if (path.find(target_index->second) != path.end()) {
	  // vertex |-> target is a back-edge
	  auto const current_lowestlink = lowestlinks.at(vertex);
	  if (target_index->second < current_lowestlink)
	    lowestlinks.insert({vertex, target_index->second});
	}
      }
    }
  }
}

Tarjans::Tarjans(const graph_t& _graph) : graph(_graph) {
  for (auto& single_source_edges : graph){// O(V)
    auto vertex = single_source_edges.first;
    if (auto i = indexes.find(vertex); i == indexes.end()){
      tarjans_loop(vertex, single_source_edges.second);
    }
  }
}
