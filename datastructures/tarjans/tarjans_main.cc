// bazel build //datastructures:tarjans_main
// clang++-10 -Wall -std=c++17 tarjans.o tarjans_main.cc
#include <cassert>
#include "tarjans.h"

int main(int argc, char* argv[]){
  using namespace tarjans;
  {
    graph_t const g = {
      {1, {}},
      {2, {}},
      {3, {}},
      {4, {}},
      {5, {}},
    };
    Tarjans t (g);
    assert(t.components.size() == 5);
  }

  {
    graph_t const g = {
      {1, {1}},
      {2, {2}},
      {3, {3}},
      {4, {4}},
      {5, {5}},
    };
    Tarjans t (g);
    assert(t.components.size() == 5);
  }

  {
    graph_t const g = {
      {1, {2}},
      {2, {3}},
      {3, {4}},
      {4, {5}},
      {5, {1}},
    };
    Tarjans t (g);
    assert(t.components.size() == 1);
  }

  {
    graph_t const g = {
      {1, {2}},
      {2, {}},
      {3, {4}},
      {4, {5}},
      {5, {3, 1}},
    };
    Tarjans t (g);
    assert(t.components.size() == 3);
  }

  {
    graph_t const g = {{1, {2}}};
    try {
      Tarjans t (g);
    }
    catch (const std::invalid_argument& e)
      {}
    } return 0;
}
