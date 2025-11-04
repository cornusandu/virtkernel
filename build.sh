#!/usr/bin/bash

set -e

args=("$@")
additionalflags="-fvisibility=hidden"

for arg in "$@"; do
    if [ "$arg" == "-g" ]; then
        echo "Using debug flags"
        additionalflags="$additionalflags -g"
    fi
done

g++ ./src/allocate/allocate.cpp ./src/statemanager.cpp $additionalflags -fPIC -shared -o ./dist/allocate.so
g++ ./src/io/io.cpp $additionalflags -fPIC -shared -o ./dist/io.so
g++ ./src/kernel.cpp ./src/statemanager.cpp $additionalflags -o ./dist/main.bin -ldl -fPIE