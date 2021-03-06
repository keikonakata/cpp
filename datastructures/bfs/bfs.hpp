#include <exception>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T, typename Hash = std::hash<T>>
class Bfs {
public:
  using nodes_t = std::vector<T>;
  using graph_t = std::unordered_map<T, nodes_t, Hash>;
  std::unordered_map<T, int, Hash> levels;
  std::unordered_map<T, T, Hash> parents;

  T parent(const T node) {
    return parents.at(node);
  }

  Bfs(const graph_t& g, T root) {
    nodes_t current;
    nodes_t next;
    auto current_level = 0;
    next.push_back(root);
    levels.insert(std::pair{root, current_level});
    parents.insert(std::pair{root, root});

    while (!next.empty()){
      current = std::move(next);
      next.clear();
      ++current_level;
      for (auto n : current) {
	auto targets = g.find(n);
	if (targets == g.end())
	  throw std::invalid_argument("vertex not found in the graph");
	for (auto target : targets->second) {
	  if (levels.find(target) == levels.end()){
	    // target is white
	    levels.insert(std::pair{target, current_level});
	    parents.insert(std::pair{target, n});
	    next.push_back(target);
	  }
	}
      }
    }
  }
};
