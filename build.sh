#!/bin/bash

NO_CACHE=""
TARGET="fms"
DOCKERFILE="Dockerfile"

for arg in "$@"; do
    case "$arg" in
        --no-cache) NO_CACHE="--no-cache" ;;
        --test) TARGET="fms_tests"; DOCKERFILE="Dockerfile.test" ;;
    esac
done

docker build $NO_CACHE -t $TARGET -f $DOCKERFILE .