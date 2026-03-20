#!/bin/bash

TARGET="fms"

for arg in "$@"; do
    case "$arg" in
        --test) TARGET="fms_tests" ;;
    esac
done

docker run --rm $TARGET