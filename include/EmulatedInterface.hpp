/**
 * File:    EmulatedInterface.hpp
 * Purpose: Emulated interface implementation example class and function declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_EMULATEDINTERFACE_
#define FMS_INCLUDE_EMULATEDINTERFACE_

#include <atomic>
#include <string>
#include <thread>
#include "Status.hpp"

namespace fms {

class EmulatedInterface
{
public:
    EmulatedInterface(std::string identifier);
    ~EmulatedInterface();

    // Get whether the hardware passes or fails. Description is out. Returns true if pass, false if fail.
    bool getHardwarePassFail(std::string& description) const;

    std::string getIdentifier() const;

    // Disable copying
    EmulatedInterface(const EmulatedInterface&)            = delete;
    EmulatedInterface& operator=(const EmulatedInterface&) = delete;

    // Disable moving
    EmulatedInterface(EmulatedInterface&&)                 = delete;
    EmulatedInterface& operator=(EmulatedInterface&&)      = delete;
private:
    void run_();

    static constexpr int MAX_FAILURE_TIME_SEC_ = 120;
    std::string identifier_;
    bool hardwarePass_ = true;

    std::atomic<bool> runFlag_ = false;
    std::thread thread_;
};

} // namespace fms

#endif // FMS_INCLUDE_EMULATEDINTERFACE_