/**
 * File:    FaultTableEntry.cpp
 * Purpose: Fault table entry class definitions.
 * Creator: Brendan College
 */

#include "FaultTableEntry.hpp"

namespace fms {

FaultTableEntry::FaultTableEntry(
    Status faultStatus,
    std::string faultGroup,
    std::string uid
) : faultStatus_(faultStatus), faultGroup_(faultGroup), uid_(uid)
{
    if (uid_.empty())
    {
        // Generate a random UID if a name or UID wasn't assigned
        uid_ = Uid::generate();
    }
}

Status FaultTableEntry::getFaultStatus() const
{
    return faultStatus_;
}

void FaultTableEntry::setFaultStatus(Status faultStatus)
{
    faultStatus_ = faultStatus;
}

const std::string& FaultTableEntry::getFaultGroup() const
{
    return faultGroup_;
}

void FaultTableEntry::setFaultGroup(const std::string& faultGroup)
{
    faultGroup_ = faultGroup;
}

const std::string& FaultTableEntry::getUid() const
{
    return uid_;
}


} // namespace fms