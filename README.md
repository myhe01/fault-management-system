# Fault Management System

This is a basic fault management system that contains a fault status table.

## Prerequisites

* Docker
* An internet connection

## Building

To build the normal application, run the build script.

```
$ ./build.sh
```

The test application can be built with the `--test` flag.

```
$ ./build.sh --test
```

Pass `--no-cache` to perform a clean build.

```
$ ./build.sh --no-cache
```
```
$ ./build.sh --test --no-cache
```

## Running

To run the normal application, use the run script.

```
$ ./run.sh
```

The test application can be run with the `--test` flag.

```
$ ./run.sh --test
```