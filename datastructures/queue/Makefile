CC=/usr/bin/clang++-12
FLAGS=-Wall -std=c++17 -pthread
#FLAGS=-Wall -stdlib=libc++ -L/usr/lib/llvm-12/lib/ -std=c++17 -pthread
COVFLAGS=-fprofile-instr-generate -fcoverage-mapping
PROFDATA=/usr/bin/llvm-profdata-12
COV=/usr/bin/llvm-cov-12

main: linked_list.hpp main.cc
	$(CC) $(FLAGS) -g -O2 main.cc -o main

fuzz: linked_list.hpp fuzz.cc
	$(CC) $(FLAGS) -g -O1 -fsanitize=fuzzer,address,undefined fuzz.cc -o fuzz
