/*
/usr/bin/clang++-10 -Wall -std=c++17 -g -O2 vector_init_profile.cc -o vector_init_profile
valgrind --tool=callgrind --simulate-cache=yes --collect-atstart=no ./vector_init_profile <mode> <len>

malloc (regardless of the size)
I-ref: 4
D-ref: 2 (1 rd + 1 wr)

reserve (regardless of the size)
I-ref: ca 2,500
D-ref: ca 1,250 (800 rd + 450 wd)

ctor
1    for I-ref: ca  3250      D-ref:  1650 (1100 rd + 600 wr)
10   for I-ref: ca  3250      D-ref:  1650 (1100 rd + 600 wr)
10^2 for I-ref: ca  3250      D-ref:  1700 (1100 rd + 600 wr)
10^3 for I-ref: ca  7250      D-ref:  5650 (1100 rd + 4600 wr)
10^4 for I-ref: ca 43,250     D-ref: 41,650 (1100 rd + 40600 wr)
10^5 for I-ref: ca 403,300    D-ref: 401,700 (1100 rd + 400,600 wr)
10^6 for I-ref: ca 4,003,300  D-ref 4,001,700 (1100 rd + 4,000,600 wr)
*/
#include <exception>
#include <vector>
#include <valgrind/callgrind.h>

using t = int;

int main(int argc, char* argv[]){
  if (argc < 3){
    throw std::invalid_argument("usage: ./a.out <mode> <len>");
  }
  const int mode = atoi(argv[1]);
  const size_t len = atoi(argv[2]);

  CALLGRIND_TOGGLE_COLLECT;
  if (mode == 0) {
    auto p = malloc(len * sizeof(t));
    free(p);
  } else if (mode == 1) {
      std::vector<t> v;
      v.reserve(len);
  } else {
      std::vector<t> v(len);
  }
  CALLGRIND_TOGGLE_COLLECT;

  return 0;
}
