/**
 * File:    FaultTableEntry.hpp
 * Purpose: Fault table entry class declarations.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FAULTABLEENTRY_
#define FMS_INCLUDE_FAULTABLEENTRY_

#include <string>
#include "Status.hpp"
#include "Uid.hpp"

namespace fms {

class FaultTableEntry
{
public:
    FaultTableEntry() = default;
    FaultTableEntry(
        Status faultStatus,
        const std::string& faultGroup = "",
        const std::string& uid = ""
    );

    Status getFaultStatus() const;
    void setFaultStatus(Status faultStatus);
    const std::string& getFaultGroup() const;
    void setFaultGroup(const std::string& faultGroup);
    const std::string& getUid() const;

private:
    void fillUid_();

    Status faultStatus_ = Status::UNINITIALIZED;
    std::string faultGroup_ = "";
    std::string uid_ = "";
};

} // namespace fms

#endif // FMS_INCLUDE_FAULTABLEENTRY_