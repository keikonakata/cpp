cc_library(
  name = "myitem",
  srcs = ["myitem.cc"],
  hdrs = ["myitem.hpp"],
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
  name = "mystack",
  srcs = ["mystack.cc", "mystack.hpp", "myitem.hpp"],
  deps = [
    ":myitem",
  ],
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