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
: camera_("camera"), gps_("gps"), fcu_("fcu"), runFlag_(true)
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
    std::string desc;
    while (runFlag_)
    {
        // Fault management logic goes here
        std::cout << "Camera status: " << (camera_.getHardwarePassFail(desc) ? "P" : "F") << std::endl;
        std::cout << "GPS status:    " << (gps_.getHardwarePassFail(desc) ? "P" : "F") << std::endl;
        std::cout << "FCU status:    " << (fcu_.getHardwarePassFail(desc) ? "P" : "F") << std::endl;
        // std::cout << "Desc: " << desc << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

Status FaultManager::getStatus() const
{
    return status_;
}

} // namespace fms