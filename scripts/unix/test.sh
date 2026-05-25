#!/usr/bin/env sh
set -eu

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure || ./build/debug/fidelio-agent-state-smoke-test
