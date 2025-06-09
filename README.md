# yadro-tapes

## Overview

The `Tape` interface was introduced to work with a tape-type device. 
The `FileBasedTape` class was inherited from it, a device that emulates operation through files.

To implement the delay during operations (read/Write/head movement), 
the `Workload` interface was introduced and the `DelayingWorkload` class was inherited. 
Delays for `DelayingWorkload` are configured via a yaml configuration file 
(the [yaml-cpp](https://github.com/jbeder/yaml-cpp) library is loaded to work with yaml files), delays represented as count of milliseconds.

The `Algorithm` interface was introduced to interact with sorting algorithms. 
Based on it, two sorting algorithms were implemented: `BubbleSortAlgorithm` and `MergeSortAlgorithm`.
`BubbleSortAlgorithm` does not use additional tapes, implements a standard algorithm without using additional memory. 
`MergeSortAlgorithm` uses two additional tapes to store temporary information.
A detailed description of the implementation of `MergeSortAlgorithm` can be found in the `docs/merge-sort-details.pdf`.

Small tests have been written for `FileBasedTape`, `BubbleSortAlgorithm`, and `MergeSortAlgorithm` using the [GoogleTest](https://github.com/google/googletest) framework.

## Build & Usage 

CMake is used to build the project. 
The targets we are interested in are `yadro_tapes` and `yadro_tapes_tests`.

The syntax for using `yadro_tapes` is as follows
```shell
yadro_tapes <input> <output> <size> <memory_limit>
```
Here, `<input>` and `<output>` are understood as input and output files, respectively (**they must exist**); 
`<size>` is the size of the tapes, respectively, input and output; 
`<memory_limit>` is memory limits (indicated by the letter M in the original condition).
The data in the tape files is stored in binary form: each cell consists of 4 bytes (it stores a 32-bit integer).

The `yadro_tapes_tests` target can be launched without additional parameters
```shell
yadro_tapes_tests
```

By default, `yadro-tapes/tmp` is used as the directory for temporary files, 
but this can be configured in the root cmake file by changing the `TMP_PATH` variable.

> [!NOTE]
> The project was built on Ubuntu (using make) and on Windows (using the built-in tools of CLion, which, apparently, 
> uses ninja under the hood). 