#include <cassert>
#include <cmath>
#include <vector>

template <typename T>
void show(const std::vector<T>& v){
  for (const auto& d: v){
    std::cout << d << ",";
  }
  std::cout << std::endl;
}

template <typename T>
class Merge {
public:
  using data_t = std::vector<T>;
  Merge(data_t& _data) : data(_data), memo(data.size()) {
    if (data.size() < 2)
      return;
    const size_t depth = std::ceil(std::log2(data.size()));
    CALLGRIND_TOGGLE_COLLECT;
    sort(depth, 0, data.size());
    CALLGRIND_TOGGLE_COLLECT;
    if (depth%2 == 1)
      data = std::move(memo);
  }
private:
  data_t& data;
  data_t memo;
  void merge(bool f, size_t b, size_t len){
    data_t* src;
    data_t* trg;
    if (f) {
      src = &data;
      trg = &memo;
    } else {
      src = &memo;
      trg = &data;
    }
    size_t half = len/2;
    size_t pos = b;
    size_t pos1 = b;
    size_t pos2 = b+half;
    while (pos1 < b+half && pos2 < b+len){
      if (src->at(pos1) < src->at(pos2)){
	trg->operator[](pos++) = std::move(src->operator[](pos1++));
      } else {
	trg->operator[](pos++) = std::move(src->operator[](pos2++));
      }
    }
    while (pos1 < b+half){
      trg->operator[](pos++) = std::move(src->operator[](pos1++));
    }
    while (pos2 < b+len){
      trg->operator[](pos++) = std::move(src->operator[](pos2++));
    }
  }
  void sort(size_t depth, size_t b, size_t len){
    if (len == 1){
      if (depth%2 == 1)
	memo.at(b) = std::move(data.at(b));
      return;
    }
    size_t half = len/2;
    sort(depth-1, b, half);
    sort(depth-1, b + half, len - half);
    merge((depth-1)%2 == 1, b, len);
  }
};

