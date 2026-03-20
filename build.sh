#!/bin/bash

if [[ "$1" == "--no-cache" ]]; then
    docker build --no-cache -t fms .
else
    docker build -t fms .
fi
