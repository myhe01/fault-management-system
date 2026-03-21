/**
 * File:    Uid.hpp
 * Purpose: UID header-only static class.
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
    static constexpr std::size_t UID_LENGTH = 8;

    static std::string generate(const std::string& seed = "")
    {
        // Use the seed if passed, else just use RNG
        std::mt19937 gen(seed.empty() ? std::random_device{}() : std::hash<std::string>{}(seed));

        std::ostringstream oss;
        oss << std::hex << std::setw(UID_LENGTH) << std::setfill('0') << gen();
        return oss.str();
    }
};

} // namespace fms

#endif // FMS_INCLUDE_UID_