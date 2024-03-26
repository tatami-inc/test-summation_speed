# Performance testing for summation strategies

## Overview

Just testing the performance of the compensated summation strategies.
Here we're testing the naive, Kahan and Neumaier methods.
Pairwise summation is assumed to be the same as naive plus some negligible overhead, so we won't bother implementing it here.

## Results

Naive summation is the fastest, as expected.
Neumaier is actually faster than Kahan, probably due to the reduced data dependency between the error and the sum.
As a happy bonus, it's also more accurate.

```console
$ ./build/summer
Expecting a sum of 77.2554

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|       16,322,771.00 |               61.26 |    1.6% |      0.18 | `naive`
|       41,066,608.00 |               24.35 |    1.4% |      0.45 | `kahan`
|       23,805,516.00 |               42.01 |    1.8% |      0.26 | `neumaier`
```

IMO the 50% penalty for Neumaier is an acceptable price to pay for never having to think about accuracy again.
Besides, we trade speed for accuracy all the time, e.g., defaulting to `double` instead of `float`, so whatever.

## Build instructions

Just use the usual CMake process:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
