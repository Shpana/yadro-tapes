# yadro-tapes

### Overview

The `Tape` interface was introduced to work with a tape-type device. 
The `FileBasedTape` class was inherited from it, a device that emulates operation through files.

To implement the delay during operations (read/write/head movement), 
the `Workload` interface was introduced and the `SleepingWorkload` class was inherited. 
Delays for `SleepingWorkload` are configured via a yaml configuration file 
(the [yaml-cpp](https://github.com/jbeder/yaml-cpp) library is loaded to work with yaml files).

The `Algorithm` interface was introduced to interact with sorting algorithms. 
Based on it, two sorting algorithms were implemented: `BubbleSortAlgorithm` and `MergeSortAlgorithm`.
`BubbleSortAlgorithm` does not use additional tapes, implements a standard algorithm without using additional memory. 
`MergeSortAlgorithm` uses two additional tapes to store temporary information.

Small tests have been written for `FileBasedTape`, `BubbleSortAlgorithm`, and `MergeSortAlgorithm` using the [GoogleTest](https://github.com/google/googletest) framework.

### Build & Usage 

CMake is used to build the project. 
The targets we are interested in are `yadro_tapes` and `run_tests`.

The syntax for using `yadro_tapes` is as follows
```shell
yadro_tapes <input> <output> <size> <memory_limit>
```
Here, `<input>` and `<output>` are understood as input and output files, respectively (**they must exist**); 
`<size>` is the size of the tapes, respectively, input and output; 
`<memory_limit>` is memory limits (indicated by the letter M in the original condition).

The `run_tests` target can be launched without additional parameters
```shell
run_tests
```

> [!NOTE]
> The project was built under Ubuntu (using make) and under Windows (using the built-in tools of CLion, which, apparently, uses ninja under the hood). 