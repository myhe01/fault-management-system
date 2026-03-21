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

    bool addFault(const FaultTableEntry& faultTableEntry);
    bool addFault(Status faultStatus, const std::string& faultGroup = "", const std::string uid = "");
    bool getFaultStatus(const std::string& uid, Status& statusOut) const;
    bool setFaultStatus(const std::string& uid, const Status status);
    bool assignFaultGroup(const std::string& uid, const unsigned int faultGroup);
    Status getGroupStatus(const unsigned int faultGroup) const;

private:
    static constexpr std::size_t MAX_FAULT_TABLE_ENTRIES_ = 64;
    std::array<FaultTableEntry, MAX_FAULT_TABLE_ENTRIES_> faultTable_;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLE_