#!/usr/bin/bash

bash -c 'cd dist; strace ./main.bin; echo "Command output: $(./main.bin)"; ./main.bin >/dev/null 2>&1; echo "Exit code: $?"'
