## Building benchmark

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .

# todo: automate
$ cp src/libc_payload.so ../lib/libc_payload.so
```

## Configuring benchmark

[not so convenient](./src/lua/embedded_script.lua)
```lua
-- CONFIGURE HERE -----------------------------
config{use_jit=true, time=60}
```

## Running benchmark

```bash
$ record-profile . ./bin/run_embedded src/lua/embedded_script.lua
# or
$ record-profile . ./bin/luajit src/lua/embedded_script.lua

$ make-flamegraph <flamegraph-name>
```
