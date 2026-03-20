/**
 * File:    FaultTable.hpp
 * Purpose: Fault table class and function declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTABLE_
#define FMS_INCLUDE_FAULTABLE_

#include <string>
#include <queue>
#include "FaultTableEntry.hpp"
#include "FixedQueue.hpp"
#include "Status.hpp"

namespace fms {

class FaultTable
{
public:
    FaultTable();
    ~FaultTable();

    bool addFault(FaultTableEntry faultTableEntry);
    Status getFaultStatus(std::string uid);
    bool setFaultStatus(Status status);

    // Count number of faults by hardware component
    unsigned int countFaults(std::string hardwareComponent);

private:
    static constexpr int MAX_FAULT_TABLE_ENTRIES_ = 64;

    FixedQueue<FaultTableEntry, MAX_FAULT_TABLE_ENTRIES_> faultTable_;
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLE_