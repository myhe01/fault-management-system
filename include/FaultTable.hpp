/**
 * File:    FaultTable.hpp
 * Purpose: Fault table class and function declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTABLE_
#define FMS_INCLUDE_FAULTABLE_

#include <array>
#include <string>
#include "FaultTableEntry.hpp"
#include "Status.hpp"

namespace fms {

/**
 * @brief Fixed-capacity table for tracking active faults.
 *
 * FaultTable stores up to MAX_FAULT_TABLE_ENTRIES FaultTableEntries. Entries can be organized into numbered fault
 * groups, and the aggregate status of a group can be queried in a single call.
 *
 * Empty slots are identified by an empty UID. Operations that search by UID will never match an empty slot.
 */
class FaultTable
{
public:
    /**
     * @brief Constructs a fault table with an array of uninitialized FaultTableEntrys.
     */
    FaultTable() = default;

    // Maximum number of fault entries the table can hold.
    static constexpr std::size_t MAX_FAULT_TABLE_ENTRIES = 64;

    /**
     * @brief Adds a pre-constructed fault entry to the table.
     *
     * Finds the first empty slot and assigns the entry to it.
     *
     * @param faultTableEntry The entry to insert.
     * @returns true if the entry was inserted, false if the table is full.
     */
    bool addFault(const FaultTableEntry& faultTableEntry);

    /**
     * @brief Constructs and adds a fault entry from a status and optional UID. If uid is empty, a random UID is
     * generated.
     *
     * @param faultStatus Initial status for the new fault entry.
     * @param uid OPTIONAL UID string. Defaults to empty (auto-generated).
     * @returns true if the entry was inserted, false if the table is full.
     */
    bool addFault(Status faultStatus, const std::string& uid = "");

    /**
     * @brief Retrieves the fault status of an entry by UID.
     *
     * @param uid The UID of the entry to look up.
     * @param statusOut OUTPUT Populated with the entry's status if found. Unchanged if not found.
     * @returns true if the entry was found, false otherwise.
     */
    bool getFaultStatus(const std::string& uid, Status& statusOut) const;

    /**
     * @brief Sets the fault status of an entry by UID.
     *
     * @param uid UID of the entry to update.
     * @param status The new status to assign.
     * @returns true if the entry was found and updated, false otherwise.
     */
    bool setFaultStatus(const std::string& uid, const Status status);

    /**
     * @brief Assigns a fault entry to a numbered fault group.
     *
     * @param uid UID of the entry to update.
     * @param faultGroup Numeric ID of the fault group to assign.
     * @returns true if the group was newly assigned to the entry, false otherwise.
     */
    bool assignFaultGroup(const std::string& uid, const unsigned int faultGroup);

    /**
     * @brief Returns the status of a fault group.
     *
     * @param faultGroup Numeric ID of the fault group to query.
     * @returns Status::FAIL if any member entry is not passing, Status::UNINITIALIZED if no entries belong to the
     * group, Status::PASS if all member entries are passing.
     */
    Status getGroupStatus(const unsigned int faultGroup) const;

private:
    // Array of fault entries. Empty slots have an empty UID.
    std::array<FaultTableEntry, MAX_FAULT_TABLE_ENTRIES> faultTable_;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLE_