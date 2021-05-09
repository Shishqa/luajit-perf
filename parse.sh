#!/usr/bin/sh

dir=$(pwd)

./scripts/lj-env "$dir/.luaenv" ./luajit/tools/luajit-parse-sysprof $@
