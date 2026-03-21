/**
 * File:    FaultTable.cpp
 * Purpose: Fault Table function definitions.
 * Creator: Brendan College
 */

#include "FaultTable.hpp"

namespace fms {

/**
 * @brief Adds a pre-constructed fault entry to the table.
 *
 * Finds the first empty slot and assigns the entry to it.
 *
 * @param faultTableEntry The entry to insert.
 * @returns true if the entry was inserted, false if the table is full.
 */
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

/**
 * @brief Constructs and adds a fault entry from a status and optional UID. If uid is empty, a random UID is generated.
 *
 * @param faultStatus Initial status for the new fault entry.
 * @param uid OPTIONAL UID string. Defaults to empty (auto-generated).
 * @returns true if the entry was inserted, false if the table is full.
 */
bool FaultTable::addFault(Status faultStatus, const std::string& uid)
{
    return addFault(FaultTableEntry(faultStatus, uid));
}

/**
 * @brief Retrieves the fault status of an entry by UID.
 *
 * @param uid The UID of the entry to look up.
 * @param statusOut OUTPUT Populated with the entry's status if found. Unchanged if not found.
 * @returns true if the entry was found, false otherwise.
 */
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

/**
 * @brief Sets the fault status of an entry by UID.
 *
 * @param uid UID of the entry to update.
 * @param status The new status to assign.
 * @returns true if the entry was found and updated, false otherwise.
 */
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

/**
 * @brief Assigns a fault entry to a numbered fault group.
 *
 * @param uid UID of the entry to update.
 * @param faultGroup Numeric ID of the fault group to assign.
 * @returns true if the group was newly assigned to the entry, false otherwise.
 */
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

/**
 * @brief Returns the status of a fault group.
 *
 * @param faultGroup Numeric ID of the fault group to query.
 * @returns Status::FAIL if any member entry is not passing, Status::UNINITIALIZED if no entries belong to the
 * group, Status::PASS if all member entries are passing.
 */
Status FaultTable::getGroupStatus(const unsigned int faultGroup) const
{
    // Number of faults in the passed group
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

            // The current fault is in the passed fault group
            countInFaultGroup++;
        }
    }

    // If we iterated through everything and didn't find any faults in that group, we'll call that group uninitialized
    if (countInFaultGroup == 0)
    {
        return Status::UNINITIALIZED;
    }

    // Iterated through group, faults exist in the group, and all faults are passing
    return Status::PASS;
}

} // namespace fms