# Simple benchmark

## Usage

```bash
# 0. clone repository
git clone --recurse-submodules https://github.com/Shishqa/luajit-perf.git

# 1. setup 
./setup.sh

# 2. run benchmark
# here you can add options
# -m [DEFAULT|LEAF|CALLGRAPH]     (profiling mode)
# -i <number>                     (profiling interval)
# -j [on|off]                     (jit mode)
# -o <path>                       (output file, default is sysprof.bin)
#
# to turn profiler on during running press Ctrl+C
# to stop execution press Ctrl+\
./run.sh ./benchmarks/mixed-recursion.lua

# 3. visualize results
./parse.sh | flamegraph.pl > flamegraph.svg
```

## TBD

* lua stack dump
* trace number dump
* installation ?
