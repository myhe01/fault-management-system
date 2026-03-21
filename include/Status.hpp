/**
 * File:    Status.hpp
 * Purpose: Fault status definitions.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_STATUS_
#define FMS_INCLUDE_STATUS_

namespace fms {

/**
 * @brief Represents the operational status of a fault or fault group.
 */
enum class Status: int
{
    UNINITIALIZED = -1,     // Entry has not been assigned a status.
    PASS = 0,               // Passing status.
    FAIL = 1                // Failing status.
};

} // namespace fms

#endif // FMS_INCLUDE_STATUS_