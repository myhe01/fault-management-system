/**
 * File:    FaultTable.cpp
 * Purpose: Fault Table function definitions.
 * Creator: Brendan College
 */

#include "FaultTable.hpp"

namespace fms {

bool FaultTable::addFault(const FaultTableEntry& faultTableEntry)
{
    // Find first empty spot in the fault table
    for (FaultTableEntry& entry : faultTable_)
    {
        if (entry.getUid().empty())
        {
            // Found an empty entry, assign the FaultTableEntry
            entry = faultTableEntry;

            // Successful entry
            return true;
        }
    }

    // No empty spots found
    return false;
}

bool FaultTable::addFault(Status faultStatus, const std::string& uid)
{
    return addFault(FaultTableEntry(faultStatus, uid));
}

bool FaultTable::getFaultStatus(const std::string& uid, Status& statusOut) const
{
    // Find the matching fault
    for (const FaultTableEntry& entry : faultTable_)
    {
        if (entry.getUid() == uid)
        {
            // Found a matching entry, get the status and return successfully
            statusOut = entry.getFaultStatus();
            return true;
        }
    }

    // No faults matched
    return false;
}

bool FaultTable::setFaultStatus(const std::string& uid, const Status status)
{
    if (uid.empty())
    {
        // Unable to match empty UID
        return false;
    }

    // Find the matching fault
    for (FaultTableEntry& entry : faultTable_)
    {
        if (entry.getUid() == uid)
        {
            // Matching fault found, set the status and return successfully
            entry.setFaultStatus(status);
            return true;
        }
    }

    // No faults matched
    return false;
}

bool FaultTable::assignFaultGroup(const std::string& uid, const unsigned int faultGroup)
{
    // Find the matching fault
    for (FaultTableEntry& entry : faultTable_)
    {
        if (entry.getUid() == uid)
        {
            // Matching fault found, set the faultGroup and return the value of assignFaultGroup()
            return entry.assignFaultGroup(faultGroup);
        }
    }

    // No faults matched
    return false;
}

Status FaultTable::getGroupStatus(const unsigned int faultGroup) const
{
    unsigned int countInFaultGroup = 0;

    // Iterate through fault table to find faults apart of group
    for (const FaultTableEntry& entry : faultTable_)
    {
        if (entry.inFaultGroup(faultGroup))
        {
            if (entry.getFaultStatus() != Status::PASS)
            {
                // Found a fault in the group that is failing
                return Status::FAIL;
            }

            countInFaultGroup++;
        }
    }

    // If we iterated through everything and didn't find any faults in that group,
    // we'll call that group uninitialized
    if (countInFaultGroup == 0)
    {
        return Status::UNINITIALIZED;
    }

    // Iterated through group, faults exist in the group, and all faults are passing
    return Status::PASS;
}

} // namespace fms