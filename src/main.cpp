/**
 * File:    main.cpp
 * Purpose: Entrypoint.
 * Creator: Brendan College
 */

#include <csignal>
#include <iostream>
#include "FaultManager.hpp"

static bool gThreadRun = true;

void signalHandler(int)
{
    gThreadRun = false;
}

int main(int argc, char* argv[])
{
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    fms::FaultManager faultManager;

    while (gThreadRun)
    {
        // Wait for interrupt
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}