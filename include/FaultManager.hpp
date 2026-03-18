/**
 * File:    FaultManager.hpp
 * Purpose: Fault Manager class and function declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTMANAGER_
#define FMS_INCLUDE_FAULTMANAGER_

#include "Status.hpp"

namespace fms {

class FaultManager
{
public:
    Status getStatus();
private:
    Status status_ = Status::UNINITIALIZED;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTMANAGER_