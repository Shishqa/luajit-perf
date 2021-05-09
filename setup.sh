#!/usr/bin/sh

echo "exporting luajit"
./scripts/export-luajit luajit .

echo "building benchmark"
mkdir -p build
cmake -S "." -B build
cmake --build build

echo "exporting libdemangle"

demangle="luajit/tools/utils/demangle/"

# костыль
cmake -S "$demangle" -B "$demangle"
cmake --build "$demangle"

cp "$demangle/libdemangle.so" ".luaenv/lib/libdemangle.so"
