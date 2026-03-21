/**
 * File:    FaultTableEntry.cpp
 * Purpose: Fault table entry class definitions.
 * Creator: Brendan College
 */

#include "FaultTableEntry.hpp"

namespace fms {

FaultTableEntry::FaultTableEntry(
    Status faultStatus,
    const std::string& uid
) : faultStatus_(faultStatus), uid_(uid)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUidIfEmpty_();
}

Status FaultTableEntry::getFaultStatus() const
{
    return faultStatus_;
}

void FaultTableEntry::setFaultStatus(Status faultStatus)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUidIfEmpty_();
    faultStatus_ = faultStatus;
}

const std::string& FaultTableEntry::getUid() const
{
    return uid_;
}

// Returns true if insertion success, false if failure
bool FaultTableEntry::assignFaultGroup(unsigned int faultGroup)
{
    fillUidIfEmpty_();
    return faultGroups_.insert(faultGroup).second;
}

bool FaultTableEntry::inFaultGroup(unsigned int faultGroup) const
{
    return faultGroups_.contains(faultGroup);
}

// Fill UID if UID is unassigned
void FaultTableEntry::fillUidIfEmpty_()
{
    if (uid_.empty())
    {
        uid_ = Uid::generate();
    }
}

} // namespace fms