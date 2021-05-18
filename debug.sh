#!/usr/bin/sh

dir=$(pwd)

./scripts/lj-env "$dir/.luaenv" gdb --args ./bin/run_embedded $@
