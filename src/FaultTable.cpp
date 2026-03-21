/**
 * File:    FaultTable.cpp
 * Purpose: Fault Table function definitions.
 * Creator: Brendan College
 */

#include <iostream>
#include "FaultTable.hpp"
#include "Status.hpp"

namespace fms {

bool FaultTable::addFault(const FaultTableEntry& faultTableEntry)
{
    // Find first empty spot in the fault table
    for (FaultTableEntry& entry : faultTable_)
    {
        if (entry.getFaultStatus() == Status::UNINITIALIZED)
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

bool FaultTable::addFault(Status faultStatus, const std::string& faultGroup, const std::string uid)
{
    // Find first empty spot in the fault table
    for (FaultTableEntry& entry : faultTable_)
    {
        if (entry.getFaultStatus() == Status::UNINITIALIZED)
        {
            // Found an empty entry, make a new FaultTableEntry and assign it
            FaultTableEntry newEntry(
                faultStatus,
                (uid.empty() ? Uid::generate() : uid)
            );
            entry = newEntry;

            // Successful entry
            return true;
        }
    }

    // No empty spots found
    return false;
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
            // Matching fault found, set the faultGroup and return successfully
            entry.assignFaultGroup(faultGroup);
            return true;
        }
    }

    // No faults matched
    return false;
}

Status FaultTable::getGroupStatus(const unsigned int faultGroup) const
{
    // Iterate through fault table to find faults apart of group
    for (const FaultTableEntry& entry : faultTable_)
    {
        if (entry.inFaultGroup(faultGroup) && entry.getFaultStatus() != Status::PASS)
        {
            // Found a fault in the group that is failing
            return Status::FAIL;
        }
    }

    // Iterated through group and all faults are passing
    return Status::PASS;
}

} // namespace fms