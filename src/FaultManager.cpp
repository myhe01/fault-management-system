/**
 * File:    FaultManager.cpp
 * Purpose: Fault Manager function definitions.
 * Creator: Brendan College
 */

#include "FaultManager.hpp"
#include "Status.hpp"

namespace fms {

Status FaultManager::getStatus()
{
    return status_;
}

} // namespace fms