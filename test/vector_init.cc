//usr/bin/clang++-10 -Wall -std=c++17 -O2 vector_init.cc
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

/*
malloc
1x 10^ 5 for 562ns
1x 10^ 6 for 141ns
1x 10^ 7 for 131ns
1x 10^ 8 for 155ns
1x 10^ 9 for 118ns
reserve
1x 10^ 5 for 51us
1x 10^ 6 for 37us
1x 10^ 7 for 33us
1x 10^ 8 for 39us
1x 10^ 9 for 53us
ctor
1x 10^ 5 for 0ms
1x 10^ 6 for 5ms
1x 10^ 7 for 60ms
1x 10^ 8 for 238ms
1x 10^ 9 for 1791ms
*/

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using t = int;

void run_malloc(const size_t len){
  auto t1 = high_resolution_clock::now();
  auto p = malloc(len * sizeof(t));
  free(p);
  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<std::chrono::nanoseconds>(t2-t1);
  const int l = std::log10(len);
  const int i = len/std::pow(10, l);
  std::cout << i << "x 10^ " << l << " for " << duration.count() << "ns\n";
}

void run_reserve(const size_t len){
  auto t1 = high_resolution_clock::now();
  {
    std::vector<t> v;
    v.reserve(len);
  }
  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<std::chrono::microseconds>(t2-t1);
  const int l = std::log10(len);
  const int i = len/std::pow(10, l);
  std::cout << i << "x 10^ " << l << " for " << duration.count() << "us\n";
}

void run_init(const size_t len){
  auto t1 = high_resolution_clock::now();
  {
    std::vector<t> v(len);
  }
  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<std::chrono::milliseconds>(t2-t1);
  const int l = std::log10(len);
  const int i = len/std::pow(10, l);
  std::cout << i << "x 10^ " << l << " for " << duration.count() << "ms\n";
}


int main(int argc, char* argv[]){
  std::cout << "malloc" << std::endl;
  for (size_t i = 5; i < 10; i++){
    run_malloc(std::pow(10,i));
  }
  std::cout << "reserve" << std::endl;
  for (size_t i = 5; i < 10; i++){
    run_reserve(std::pow(10,i));
  }
  std::cout << "ctor" << std::endl;
  for (size_t i = 5; i < 10; i++){
    run_init(std::pow(10,i));
  }

  return 0;
}
