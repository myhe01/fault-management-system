/**
 * File:    FaultTableEntry.hpp
 * Purpose: Fault table entry class declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTABLEENTRY_
#define FMS_INCLUDE_FAULTABLEENTRY_

#include <string>
#include <unordered_set>
#include "Status.hpp"
#include "Uid.hpp"

namespace fms {

/**
 * @brief A single entry in the fault table.
 *
 * Each entry carries a unique identifier (UID), a fault status, and an optional set of fault group memberships.
 *
 * A default-constructed entry has an empty UID and is treated as an unoccupied slot by FaultTable. A UID is assigned
 * the first time the entry is actively used (via the parameterized constructor, setFaultStatus, or assignFaultGroup).
 */
class FaultTableEntry
{
public:
    /**
     * @brief Constructs an empty, unoccupied fault table slot.
     */
    FaultTableEntry() = default;

    /**
     * @brief Constructs an active fault table entry.
     *
     * If no UID is provided or the provided UID is empty, a random UID is generated automatically.
     *
     * @param faultStatus Initial fault status for this entry.
     * @param uid OPTIONAL UID string. If empty, one is auto-generated.
     */
    FaultTableEntry(
        Status faultStatus,
        const std::string& uid = ""
    );

    /**
     * @brief Returns the current fault status of this entry.
     * @returns The current Status value.
     */
    Status getFaultStatus() const;

    /**
     * @brief Sets the fault status of this entry. If the UID is currently empty, a UID is generated.
     *
     * @param faultStatus The new Status value to assign.
     */
    void setFaultStatus(Status faultStatus);

    /**
     * @brief Returns the UID of this entry.
     * @returns A const reference to the UID string.
     */
    const std::string& getUid() const;

    /**
     * @brief Assigns this entry to a fault group.
     *
     * Inserts the given group ID into the entry's fault group set. If the entry is already a member of the group, the
     * call has no effect and returns false. If the UID is empty, one is generated before insertion.
     *
     * @param faultGroup Numeric ID of the fault group to join.
     * @returns true if the group was newly added, false if already a member or if insertion failed.
     */
    bool assignFaultGroup(unsigned int faultGroup);

    /**
     * @brief Checks whether this entry belongs to a given fault group.
     * @param faultGroup Numeric ID of the fault group to query.
     * @returns true if this entry is a member of the group, false otherwise.
     */
    bool inFaultGroup(unsigned int faultGroup) const;

private:
    Status faultStatus_ = Status::UNINITIALIZED;            // Current fault status.
    std::string uid_ = "";                                  // Unique identifier. Empty if unoccupied.
    std::unordered_set<unsigned int> faultGroups_;          // Unordered set of fault group memberships.

    /**
     * @brief Generates and assigns a UID if the current UID is empty. Promotes a slot to an active entry on first use.
     */
    void fillUidIfEmpty_();
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLEENTRY_