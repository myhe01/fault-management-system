/**
 * File:    Uid.hpp
 * Purpose: UID static class.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_UID_
#define FMS_INCLUDE_UID_

#include <iomanip>
#include <random>
#include <sstream>
#include <string>

namespace fms {

class Uid
{
public:
    static std::string generateUid(const std::string& seed = "")
    {
        // Use the seed if passed, else just use RNG
        std::mt19937 gen(seed.empty() ? std::random_device{}() : std::hash<std::string>{}(seed));

        std::ostringstream oss;
        oss << std::hex << std::setw(8) << std::setfill('0') << gen();
        return oss.str();
    }
};

} // namespace fms

#endif // FMS_INCLUDE_UID_