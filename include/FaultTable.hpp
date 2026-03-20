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

class FaultTable
{
public:
    FaultTable() = default;
    ~FaultTable() = default;

    bool addFault(FaultTableEntry& faultTableEntry);
    bool removeFault(std::string uid);
    bool getFaultStatus(std::string uid, Status& statusOut) const;
    bool setFaultStatus(std::string uid, Status status);
    Status getGroupStatus(std::string faultGroup) const;

private:
    int getFaultIndexByUid_(std::string uid) const;

    static constexpr std::size_t MAX_FAULT_TABLE_ENTRIES_ = 64;
    std::array<FaultTableEntry, MAX_FAULT_TABLE_ENTRIES_> faultTable_;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLE_