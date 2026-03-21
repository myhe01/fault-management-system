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

class FaultTableEntry
{
public:
    FaultTableEntry() = default;
    FaultTableEntry(
        Status faultStatus,
        const std::string& uid = ""
    );

    Status getFaultStatus() const;
    void setFaultStatus(Status faultStatus);
    const std::string& getUid() const;

    bool assignFaultGroup(unsigned int faultGroup);
    bool inFaultGroup(unsigned int faultGroup) const;

private:
    Status faultStatus_ = Status::UNINITIALIZED;
    std::string uid_ = "";
    std::unordered_set<unsigned int> faultGroups_;

    void fillUidIfEmpty_();
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLEENTRY_