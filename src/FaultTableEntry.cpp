/**
 * File:    FaultTableEntry.cpp
 * Purpose: Fault table entry class definitions.
 * Creator: Brendan College
 */

#include "FaultTableEntry.hpp"

namespace fms {

FaultTableEntry::FaultTableEntry(
    Status faultStatus,
    const std::string& faultGroup,
    const std::string& uid
) : faultStatus_(faultStatus), faultGroup_(faultGroup), uid_(uid)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUid_();
}

Status FaultTableEntry::getFaultStatus() const
{
    return faultStatus_;
}

void FaultTableEntry::setFaultStatus(Status faultStatus)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUid_();
    faultStatus_ = faultStatus;
}

const std::string& FaultTableEntry::getFaultGroup() const
{
    return faultGroup_;
}

void FaultTableEntry::setFaultGroup(const std::string& faultGroup)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUid_();
    faultGroup_ = faultGroup;
}

const std::string& FaultTableEntry::getUid() const
{
    return uid_;
}

// Fill UID if UID is unassigned
void FaultTableEntry::fillUid_()
{
    if (uid_.empty())
    {
        uid_ = Uid::generate();
    }
}

} // namespace fms