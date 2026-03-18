/**
 * File:    Status.hpp
 * Purpose: Fault status definitions.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_STATUS_
#define FMS_INCLUDE_STATUS_

namespace fms {

enum class Status: int
{
    Status_Begin_,
    UNINITIALIZED = -1,
    PASS = 0,
    FAIL = 1,
    Status_End_
};

} // namespace fms

#endif // FMS_INCLUDE_STATUS_