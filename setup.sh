#!/usr/bin/sh

echo "exporting luajit"
sudo ./scripts/export-luajit luajit .

echo "building benchmark"
mkdir -p build
cmake -S "." -B build
cmake --build build

echo "gaining access rights to luajit-parse-sysprof"
sudo chown $(whoami) /usr/local/bin/luajit-parse-sysprof
