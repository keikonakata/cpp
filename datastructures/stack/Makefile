CC=/usr/bin/clang++-10
FLAGS=-Wall -std=c++17
COVFLAGS=-fprofile-instr-generate -fcoverage-mapping
PROFDATA=/usr/bin/llvm-profdata-10
COV=/usr/bin/llvm-cov-10

main_cov: linked_list.hpp main.cc
	$(CC) $(FLAGS) $(COVFLAGS) main.cc -o main_cov

coverage: main_cov
	LLVM_PROFILE_FILE="linked_list.profraw" ./main_cov &&\
	$(PROFDATA) merge -sparse linked_list.profraw -o linked_list.profdata &&\
	$(COV) show ./main_cov -instr-profile=./linked_list.profdata
