/**
 * File:    EmulatedInterface.cpp
 * Purpose: Emulated interface example function definitions.
 * Creator: Brendan College
 */

#include <random>
#include "EmulatedInterface.hpp"

namespace fms {

EmulatedInterface::EmulatedInterface(std::string identifier)
: identifier_(identifier), runFlag_(true)
{
    thread_  = std::thread(&EmulatedInterface::run_, this);
}

EmulatedInterface::~EmulatedInterface()
{
    runFlag_ = false;
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void EmulatedInterface::run_()
{
    std::random_device ranDev;
    std::mt19937 gen(ranDev());
    std::size_t iterCount_ = 0;

    while (runFlag_)
    {
        // Randomly generate a hardware failure
        std::uniform_int_distribution<int> dist(1, 100);
        int roll = dist(gen);

        // Probability of failure increases each iteration (100ms intervals)
        double elapsed = static_cast<double>(iterCount_);
        double threshold = (elapsed / MAX_FAILURE_TIME_SEC_) * 100.0;

        if (roll <= static_cast<int>(threshold))
        {
            // Set variable that indicates a hardware failure
            hardwarePass_ = false;
            return;
        }

        ++iterCount_;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Get whether the hardware is passing or if there's a failure
bool EmulatedInterface::getHardwarePassFail(std::string& description) const
{
    description = (hardwarePass_ ? "pass" : "fail");
    return hardwarePass_;
}

std::string EmulatedInterface::getIdentifier() const
{
    return identifier_;
}

} // namespace fms