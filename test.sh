#!/bin/bash

set -euo pipefail

SIZE=$1
PUSH_SWAP=${2:-./push_swap}

ITERATIONS=30

run() {
  local values=()

  while [ "${#values[@]}" -lt "$SIZE" ]; do
    value=$(( ($RANDOM % (2 * $SIZE)) - $SIZE ))

    if ! echo "${values[@]}" | grep -wq -- "$value"; then
      values+=("$value")
    fi
  done

  "$PUSH_SWAP" "${values[@]}" 2> /dev/null
}

counts=()
for _ in $(seq "$ITERATIONS"); do
  counts+=("$(run | wc -l)")
done

echo "${counts[@]}" | awk '
  {
    sum += $1
    max = max > $1 ? max : $1
  }

  END {
    print "avg:", sum / NR
    print "worst:", max
  }' RS=" "
