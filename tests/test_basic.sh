#!/usr/bin/env bash
set -euo pipefail

if [ ! -f "./app" ]; then
  make
fi

output=$(printf "2 3\n" | ./app)
echo "$output" | grep -q "Result: 5" && echo "✅ Test passed"
