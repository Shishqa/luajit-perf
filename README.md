# Simple benchmark

## Usage

#### 1. Export LuaJIT

Find your favourite build of luaJIT and export it to the project with
```bash
$ ./scripts/export-luajit <path-to-luajit-repo-root> .
```

#### 2. Build benchmark

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

#### 3. Run

```bash
$ lj-env .luaenv ./bin/run_benchmark
```

### Building LuaJIT with perf tools support

To build luaJIT with perf tools support add flag `-DLUAJIT_USE_PERFTOOLS`

## Configuring benchmark

[not so convenient](./src/run_payloads.lua)
```lua
-- CONFIGURE HERE -----------------------------
config{use_jit=true, time=60}
```

## Running benchmark for perf

```bash
$ record-profile ./bin/run_benchmark
# or
$ record-profile ./.luaenv/bin/luajit src/lua/run_payloads.lua

$ make-flamegraph <flamegraph-name>
```

## Running benchmark for custom profiler
``` bash
$ lj-env . ./bin/run_embedded src/lua/run_payloads.lua out.nofold
```
