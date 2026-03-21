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

static bool gThreadRun = true;      // GLOBAL Thread run flag. Set to false to trigger a clean shutdown.

/**
 * @brief Signal handler for SIGINT and SIGTERM.
 *
 * Sets the global run flag to false, causing the main loop to exit on its next iteration. The FaultTable is then
 * destroyed cleanly as it goes out of scope.
 */
void signalHandler(int)
{
    gThreadRun = false;
}

int main()
{
    // Register signals
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    fms::FaultTable faultTable_;

    while (gThreadRun)
    {
        // Wait for signal
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}