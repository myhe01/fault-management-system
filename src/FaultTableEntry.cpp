/**
 * File:    FaultTableEntry.cpp
 * Purpose: Fault table entry class definitions.
 * Creator: Brendan College
 */

#include "FaultTableEntry.hpp"

namespace fms {

/**
 * @brief Constructs an active fault table entry.
 *
 * If no UID is provided or the provided UID is empty, a random UID is generated automatically.
 *
 * @param faultStatus Initial fault status for this entry.
 * @param uid OPTIONAL UID string. If empty, one is auto-generated.
 */
FaultTableEntry::FaultTableEntry(
    Status faultStatus,
    const std::string& uid
) : faultStatus_(faultStatus), uid_(uid)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUidIfEmpty_();
}

/**
 * @brief Returns the current fault status of this entry.
 * @returns The current Status value.
 */
Status FaultTableEntry::getFaultStatus() const
{
    return faultStatus_;
}

/**
 * @brief Sets the fault status of this entry. If the UID is currently empty, a UID is generated.
 *
 * @param faultStatus The new Status value to assign.
 */
void FaultTableEntry::setFaultStatus(Status faultStatus)
{
    // Fill the UID if this FaultTableEntry is going to be used
    fillUidIfEmpty_();
    faultStatus_ = faultStatus;
}

/**
 * @brief Returns the UID of this entry.
 * @returns A const reference to the UID string.
 */
const std::string& FaultTableEntry::getUid() const
{
    return uid_;
}

/**
 * @brief Assigns this entry to a fault group.
 *
 * Inserts the given group ID into the entry's fault group set. If the entry is already a member of the group, the call
 * has no effect and returns false. If the UID is empty, one is generated before insertion.
 *
 * @param faultGroup Numeric ID of the fault group to join.
 * @returns true if the group was newly added, false if already a member or if insertion failed.
 */
bool FaultTableEntry::assignFaultGroup(unsigned int faultGroup)
{
    fillUidIfEmpty_();
    return faultGroups_.insert(faultGroup).second;
}

/**
 * @brief Checks whether this entry belongs to a given fault group.
 * @param faultGroup Numeric ID of the fault group to query.
 * @returns true if this entry is a member of the group, false otherwise.
 */
bool FaultTableEntry::inFaultGroup(unsigned int faultGroup) const
{
    return faultGroups_.contains(faultGroup);
}

/**
 * @brief Generates and assigns a UID if the current UID is empty. Promotes a slot to an active entry on first use.
 */
void FaultTableEntry::fillUidIfEmpty_()
{
    if (uid_.empty())
    {
        uid_ = Uid::generate();
    }
}

} // namespace fms