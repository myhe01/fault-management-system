/**
 * File:    FaultManager.cpp
 * Purpose: Fault Manager function definitions.
 * Creator: Brendan College
 */

#include <iostream>
#include "FaultManager.hpp"
#include "Status.hpp"

namespace fms {

FaultManager::FaultManager()
: camera_("camera"), gps_("gps"), fcu_("fcu"), faultTable_(), runFlag_(true)
{
    thread_ = std::thread(&FaultManager::run_, this);
}

FaultManager::~FaultManager()
{
    runFlag_ = false;
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void FaultManager::run_()
{
    while (runFlag_)
    {
        // Perform fault management checks
        checkCameraForFaults();
        checkGpsForFaults();
        checkFcuForFaults();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void FaultManager::checkCameraForFaults()
{
    std::string desc;
    std::cout << "Camera status: " << (camera_.getHardwarePassFail(desc) ? "P" : "F") << std::endl;

    unsigned int numFaults = faultTable_.countFaults(camera_.getIdentifier());
    if (numFaults < 1)
    {
        // Add to fault table
    }
}

void FaultManager::checkGpsForFaults()
{
    std::string desc;
    std::cout << "GPS status:    " << (gps_.getHardwarePassFail(desc) ? "P" : "F") << std::endl;
}

void FaultManager::checkFcuForFaults()
{
    std::string desc;
    std::cout << "FCU status:    " << (fcu_.getHardwarePassFail(desc) ? "P" : "F") << std::endl;
}

Status FaultManager::getStatus() const
{
    return status_;
}

} // namespace fms