#ifndef DFS_NOREC_HPP_INCLUDED
#define DFS_NOREC_HPP_INCLUDED

#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T>
class DfsNorec {
public:
  using node_t = T;
  using nodes_t = std::vector<node_t>;
  using graph_t = std::unordered_map<T, nodes_t>;
 nodes_t nodes; // in topological ordering
  DfsNorec(const graph_t& g){
    visited_t visited;
    for (auto& n : g) {
      auto root = n.first;
      if (visited.find(root) == visited.end()){
	visited.emplace(root);
	dfs_loop(g, visited, root, n.second);
      }
    }
  }
private:
  using todos_t = std::vector<std::tuple<node_t, typename nodes_t::const_iterator, typename nodes_t::const_iterator>>;
  using visited_t = std::unordered_set<node_t>;

  void dfs_loop(const graph_t& g, visited_t& visited, node_t root, const nodes_t& edges){
    todos_t todos;
    todos.emplace_back(root, edges.cbegin(), edges.cend());
    while (!todos.empty()){
      auto& todo = todos.back();
      if (std::get<1>(todo) == std::get<2>(todo)){
	// std::get<0>(todo) is black
	nodes.emplace_back(std::get<0>(todo));
	todos.pop_back();
      } else {
	// std::get<0>(todo) is gray
	auto target = *std::get<1>(todo);
	std::advance(std::get<1>(todo), 1);
	if (auto it = visited.find(target); it == visited.end()){
	  // target is white
	  visited.emplace(target);
	  const auto target_edges = g.find(target);
	  if (target_edges == g.end())
	    throw std::invalid_argument("vertex not in the graph");
	  todos.emplace_back(target, target_edges->second.cbegin(), target_edges->second.cend());
	} else {
	  // target is gray or black
	  // no-op
	}
      }
    }
  }
};


#endif /* DFS_NOREC_HPP_INCLUDED */
