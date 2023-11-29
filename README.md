## Stanford CS106L

This is Stanford CS106L: Standard C++ Programming, Autumn 2023.

Course website: http://web.stanford.edu/class/cs106l/index.html

In this course, I reviewed my C++ skills, understood a lot of concepts and well prepared for CS144.
However, the assignments are too easy to complete.
I cost more time on reading the whole implement -- unordered_map is interesting.
I believe the CS144 warmup assignment will be much more challenging.

This project use the modern LLVM (17.0.4) toolchain -- clang++ as build system, clangd as LSP, lldb as debugger.
Follow the [instruction](https://apt.llvm.org/) to install them.
For more my code can be found at: https://github.com/iyume/cpp-experience

## Benchmark?

Build command: `clang++-17 -g -std=c++17 -o assignment2/main assignment2/main.cpp`

```txt
----- Milestone 2 Tests -----
Test A_copy_ctor_basic              PASS
Test B_copy_assign_basic            PASS
Test C_copy_edge                    PASS
Test D_move_ctor_basic              PASS
Test E_move_assign_basic            PASS
Test F_move_edge                    PASS
Move    10 elements: 40 ns
Move   100 elements: 30 ns
Move  1000 elements: 30 ns
Move 10000 elements: 40 ns
Test G_move_ctor_time               PASS
Move    10 elements: 301 ns
Move   100 elements: 140 ns
Move  1000 elements: 140 ns
Move 10000 elements: 130 ns
Test H_move_assign_time             PASS

----- Test Harness Summary -----
Required Tests passed: 8/8
You passed all required tests! Great job!

----- End of Test Harness -----
```

Build command: `clang++-17 -O3 -std=c++17 -o assignment2/main assignment2/main.cpp`

```txt
----- Milestone 2 Tests -----
Test A_copy_ctor_basic              PASS
Test B_copy_assign_basic            PASS
Test C_copy_edge                    PASS
Test D_move_ctor_basic              PASS
Test E_move_assign_basic            PASS
Test F_move_edge                    PASS
Move    10 elements: 50 ns
Move   100 elements: 30 ns
Move  1000 elements: 20 ns
Move 10000 elements: 20 ns
Test G_move_ctor_time               PASS
Move    10 elements: 90 ns
Move   100 elements: 20 ns
Move  1000 elements: 21 ns
Move 10000 elements: 40 ns
Test H_move_assign_time             PASS

----- Test Harness Summary -----
Required Tests passed: 8/8
You passed all required tests! Great job!

----- End of Test Harness -----
```

> The speed of optimized build is extremely fast so that some insertions failed sometimes. See tests.cpp:1680 `// you should be able to easily beat this benchmark if you actually implemented move`
