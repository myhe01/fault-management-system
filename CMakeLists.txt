cmake_minimum_required(VERSION 3.25)

project(fms
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clangd / tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
add_executable(fms
    src/main.cpp
    src/EmulatedInterface.cpp
    src/FaultManager.cpp
)

target_include_directories(fms PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(fms PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wno-unused-parameter
    -Werror
)

# External dependencies (add yours here)
# find_package(spdlog REQUIRED)
# target_link_libraries(fms PRIVATE spdlog::spdlog)

install(TARGETS fms RUNTIME DESTINATION bin)
