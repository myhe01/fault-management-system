/**
 * File:    main.cpp
 * Purpose: Entrypoint.
 * Creator: Brendan College
 */

#include <csignal>
#include <chrono>
#include <iostream>
#include <thread>
#include "FaultTable.hpp"

static bool gThreadRun = true;

void signalHandler(int)
{
    gThreadRun = false;
}

int main()
{
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    fms::FaultTable faultTable_;

    while (gThreadRun)
    {
        // Wait for interrupt
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}