# cpp
- [On member initializer list vs default member initializer](https://stackoverflow.com/questions/36600187/whats-the-differences-between-member-initializer-list-and-default-member-initia)

  Members are initialized in the sequence in which they are declared in the class (irrespective of the order in the member initializer list).

> const applies to the thing left of it. If there is nothing on the left then it applies to the thing right of it.

[Understanding when not to std::move in C++](https://developers.redhat.com/blog/2019/04/12/understanding-when-not-to-stdmove-in-c)

[Range-based for loop](https://en.cppreference.com/w/cpp/language/range-for)

> It is safe, and in fact, preferable in generic code, to use deduction to forwarding reference, for `(auto&& var : sequence)`.

- iterator invalidation
  - hash : insertion will invalidate iterators if it causes rehash. erase will only invalidate the element erased.
  - map : insertion will not invalidate iterators

HERE

https://clang.llvm.org/docs/SourceBasedCodeCoverage.html

https://en.cppreference.com/w/cpp/language/try_catch

https://clang.llvm.org/docs/DataFlowAnalysisIntro.html

https://artificial-mind.net/blog/2021/10/23/return-moves

https://clang.llvm.org/docs/index.html (various topics)

https://blog.quasar.ai/using-c-containers-efficiently

Exception and cost

what is fowarding reference 'auto&&'

[CppCon 2014 Chandler Carrush]https://www.youtube.com/watch?v=fHNmRkzxHWs)
Efficiency with Algorithms, Performance with Data structures
