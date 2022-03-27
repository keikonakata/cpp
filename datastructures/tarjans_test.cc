// bazel test --test_output=all //datastructures:tarjans_test
#include <gtest/gtest.h>
#include <iostream>
#include "tarjans.h"

TEST(BasicTest, Disjoint5){
  using namespace tarjans;
  graph_t const g = {
    {1, {}},
    {2, {}},
    {3, {}},
    {4, {}},
    {5, {}},
  };
  Tarjans t (g);
  EXPECT_EQ(t.components.size(), 5);
}

TEST(BasicTest, DisjointLoop5){
  using namespace tarjans;
  graph_t const g = {
    {1, {1}},
    {2, {2}},
    {3, {3}},
    {4, {4}},
    {5, {5}},
  };
  Tarjans t (g);
  EXPECT_EQ(t.components.size(), 5);
}

TEST(BasicTest, Line5){
  using namespace tarjans;
  graph_t const g = {
    {1, {2}},
    {2, {3}},
    {3, {4}},
    {4, {5}},
    {5, {5}},
  };
  Tarjans t (g);
  EXPECT_EQ(t.components.size(), 5);
}

TEST(BasicTest, Loop){
  using namespace tarjans;
  graph_t const g = {
    {1, {2}},
    {2, {3}},
    {3, {4}},
    {4, {5}},
    {5, {1}},
  };
  Tarjans t (g);
  EXPECT_EQ(t.components.size(), 1);
}

TEST(BasicTest, C2){
  using namespace tarjans;
  graph_t const g = {
    {1, {2}},
    {2, {}},
    {3, {4}},
    {4, {5}},
    {5, {3, 1}},
  };
  Tarjans t (g);
  EXPECT_EQ(t.components.size(), 3);
}
