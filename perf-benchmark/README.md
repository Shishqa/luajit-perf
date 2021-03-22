## Building benchmark

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

### Building LuaJIT with perf tools support

To build luaJIT with perf tools support add flag `-DLUAJIT_USE_PERFTOOLS`

## Configuring benchmark

[not so convenient](./src/lua/run_payloads.lua)
```lua
-- CONFIGURE HERE -----------------------------
config{use_jit=true, time=60}
```

## Running benchmark

```bash
$ record-profile ./bin/run_embedded src/lua/run_payloads.lua
# or
$ record-profile ./bin/luajit src/lua/run_payloads.lua

$ make-flamegraph <flamegraph-name>
```
