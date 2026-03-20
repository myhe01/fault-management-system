/**
 * File:    FaultTableEntry.hpp
 * Purpose: Fault table header-only class declarations and definitions.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTABLEENTRY_
#define FMS_INCLUDE_FAULTABLEENTRY_

#include <string>
#include "Status.hpp"

namespace fms {

class FaultTableEntry
{
public:
    FaultTableEntry(
        std::string uid,
        std::string hardwareIdentifier,
        std::string description,
        Status faultStatus = Status::UNINITIALIZED
    )
    : uid_(uid), hardwareIdentifier_(hardwareIdentifier), description_(description), faultStatus_(faultStatus)
    {}

    std::string getUid() const
    {
        return uid_;
    }

    std::string getHardwareIdentifier() const
    {
        return hardwareIdentifier_;
    }

    std::string getDescription() const
    {
        return description_;
    }

    Status getFaultStatus() const
    {
        return faultStatus_;
    }

    void setFaultStatus(Status faultStatus)
    {
        faultStatus_ = faultStatus;
    }

private:
    std::string uid_;
    std::string hardwareIdentifier_;
    std::string description_;
    Status faultStatus_;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLEENTRY_