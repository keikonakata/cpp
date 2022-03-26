cc_binary(
  name = "bfs",
  srcs = ["bfs.cc"]
)

cc_binary(
  name = "disjoint_set",
  srcs = ["disjoint_set.cc", "disjoint_set.hpp"],
)
cc_binary(
  name = "pstack",
  srcs = ["pstack.cc", "pstack.hpp", "myitem.hpp"],
  deps = [
    ":myitem",
  ],
  linkopts = ["-lpthread"],
)

cc_binary(
  name = "mst_kruskal",
  srcs = ["mst_kruskal.cc", "disjoint_set.hpp"],
)
cc_binary(
  name = "mystack",
  srcs = ["mystack.cc", "mystack.hpp", "myitem.hpp"],
  deps = [
    ":myitem",
  ],
)

cc_library(
  name = "myitem",
  srcs = ["myitem.cc"],
  hdrs = ["myitem.hpp"],
)

cc_library(
  name = "tarjans",
  srcs = ["tarjans.cc"],
  hdrs = ["tarjans.h"],
)

cc_test(
  name = "mystack_test",
  size = "small",
  srcs = ["mystack_test.cc", "myitem.hpp", "mystack.hpp"],
  deps = [
    "@com_google_googletest//:gtest_main",
    ":myitem",
  ],
)