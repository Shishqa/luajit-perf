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
$ lj-env .luaenv ./bin/prof_bench
```

It will produce output to `out.nofold` file

### To see unexpected behaviour

1. checkout to `shishqa/shared-objects` branch in luajit fork
2. `export-luajit` to this repository root
3. build benchmark (2)
4. run it with `lj-env .luaenv ./scripts/run_infinitely ./bin/prof_bench`

> `bad func` means current frame couldn't recognize, which func
> it belongs to

### Building LuaJIT with perf tools support

To build luaJIT with perf tools support add flag `-DLUAJIT_USE_PERFTOOLS`

## Configuring benchmark

[not so convenient](./src/run_payloads.lua)
```lua
-- CONFIGURE HERE -----------------------------
config{use_jit=true, time=60}
```

