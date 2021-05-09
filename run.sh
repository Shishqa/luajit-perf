#!/usr/bin/sh

dir=$(pwd)

./scripts/lj-env "$dir/.luaenv" ./bin/run_embedded $@
