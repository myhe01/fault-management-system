/**
 * File:    FaultTable.cpp
 * Purpose: Fault Table function definitions.
 * Creator: Brendan College
 */

#include <iostream>
#include "FaultTable.hpp"
#include "Status.hpp"

namespace fms {

bool FaultTable::addFault(FaultTableEntry& faultTableEntry)
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

bool FaultTable::removeFault(std::string uid)
{
    // Find matching fault's index
    int index = getFaultIndexByUid_(uid);

    if (index < 0)
    {
        // No matching fault found
        return false;
    }

    // Found a matching entry, assign it to an empty FaultTableEntry
    faultTable_[index] = FaultTableEntry();

    // Successful removal
    return true;
}

bool FaultTable::getFaultStatus(std::string uid, Status& statusOut) const
{
    // Find matching fault's index
    int index = getFaultIndexByUid_(uid);

    if (index < 0)
    {
        // No matching fault found
        return false;
    }

    // Found a matching entry
    statusOut = faultTable_[index].getFaultStatus();
    return true;
}

bool FaultTable::setFaultStatus(std::string uid, Status status)
{
    // Find matching fault's index
    int index = getFaultIndexByUid_(uid);

    if (index < 0)
    {
        // No matching fault found
        return false;
    }

    // Found a matching entry
    faultTable_[index].setFaultStatus(status);
    return true;
}

// Returns -1 when no match found, and between 0 and (MAX_FAULT_TABLE_ENTRIES_ - 1) if match found
int FaultTable::getFaultIndexByUid_(std::string uid) const
{
    // Find first matching fault in the fault table
    for (std::size_t i = 0; i < MAX_FAULT_TABLE_ENTRIES_; i++)
    {
        if (faultTable_[i].getUid() == uid)
        {
            // We found a matching entry, return its index
            return static_cast<int>(i);
        }
    }

    // No matching fault found, return negative
    return -1;
}

} // namespace fms