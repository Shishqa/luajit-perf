## Install

```bash
$ git clone ...
$ git submodule update --init --recursive
$ ./scripts/export-luajit ./luajit ./perf-benchmark
$ cd perf-benchmark
$ lj-env . ./bin/luajit --version
```

## Scripts
- `export-luajit` builds luajit and installs it to specified directory

  usage: `export-luajit <luajit_folder> <install_prefix>`

- `lj-env` sets `LUA_PATH` and `LUA_CPATH` according to `<install_prefix>`

  usage: `lj-env <install_prefix> <command> [args...]`

- `record-profile` runs `perf record` inside luajit environment set by `lj-env`

- `make-flamegraph` exports `perf report` as flamegraph to `./flamegraphs/` 
  folder

  Warning: it depends on `$BROWSER` environment variable to display flamegraph

- `fold.py` folds call chains acquired by profiler

  usage: `fold.py out.nofold > out.fold`

> for convenience script folder can be added to `$PATH`
