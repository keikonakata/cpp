CC=/usr/bin/clang++-10
FLAGS=-Wall -std=c++17
COVFLAGS=-fprofile-instr-generate -fcoverage-mapping
PROFDATA=/usr/bin/llvm-profdata-10
COV=/usr/bin/llvm-cov-10

tarjans.o: tarjans.h tarjans.cc
	$(CC) $(FLAGS)  -c tarjans.cc -o tarjans.o

tarjans_cov.o: tarjans.h tarjans.cc
	$(CC) $(FLAGS) $(COVFLAGS) -c tarjans.cc -o tarjans_cov.o

tarjans_main_cov: tarjans.h tarjans.cc tarjans_main.cc
	$(CC) $(FLAGS) $(COVFLAGS) tarjans.cc tarjans_main.cc -o tarjans_main_cov

tarjans_coverage: tarjans_main_cov
	LLVM_PROFILE_FILE="tarjans.profraw" ./tarjans_main_cov &&\
	$(PROFDATA) merge -sparse tarjans.profraw -o tarjans.profdata &&\
	$(COV) show ./tarjans_main_cov -instr-profile=./tarjans.profdata

tarjans_fuzz: tarjans.cc tarjans_fuzz.cc
	$(CC) $(FLAGS) -g -O1 -fsanitize=fuzzer,address,undefined tarjans.cc tarjans_fuzz.cc -o tarjans_fuzz
