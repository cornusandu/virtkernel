#!/usr/bin/bash

set -e

g++ ./src/allocate/allocate.cpp -fPIC -shared -o ./dist/allocate.so -nostartfiles
g++ ./src/kernel.cpp ./src/statemanager.cpp -fPIE -o ./dist/main.bin -Wl,-e,_boot