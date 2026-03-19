/**
 * File:    FaultManager.hpp
 * Purpose: Fault Manager class and function declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTMANAGER_
#define FMS_INCLUDE_FAULTMANAGER_

#include <atomic>
#include <thread>
#include "EmulatedInterface.hpp"
#include "Status.hpp"

namespace fms {

class FaultManager
{
public:
    FaultManager();
    ~FaultManager();

    // Disable copying
    FaultManager(const FaultManager&)            = delete;
    FaultManager& operator=(const FaultManager&) = delete;

    // Disable moving
    FaultManager(FaultManager&&)                 = delete;
    FaultManager& operator=(FaultManager&&)      = delete;

    Status getStatus() const;
private:
    void run_();

    EmulatedInterface camera_, gps_, fcu_;
    Status status_ = Status::UNINITIALIZED;
    std::atomic<bool> runFlag_ = false;
    std::thread thread_;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTMANAGER_