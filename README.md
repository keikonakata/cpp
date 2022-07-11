## Hardware

Ubuntu on Dell XPS 13 9360 (075B)

Processor: Intel Core i7-7500U CPU @ 2.70Ghz, 2 cores, 4 threads with HyperThreading

Memory 8GiB, 2 banks 4GiB each, 64-bit width, 1867MHz (0.5ns)

Cache 128KiB (64KiB instruction + 64KiB data) L1, 512KiB L2, 4MiB L3

as per `lscpu` and `lshw -C memory`.

## Notes

- [Clang sanitizers](https://github.com/google/sanitizers)

- [On member initializer list vs default member initializer](https://stackoverflow.com/questions/36600187/whats-the-differences-between-member-initializer-list-and-default-member-initia)

  >  Members are initialized in the sequence in which they are declared in the class (irrespective of the order in the member initializer list).

