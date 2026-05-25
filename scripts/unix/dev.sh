#!/usr/bin/env sh
set -eu

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

cmake --preset debug
cmake --build --preset debug

if [ "$#" -eq 0 ]; then
  set -- status
fi

./build/debug/fidelio-loyalty-agent "$@"
