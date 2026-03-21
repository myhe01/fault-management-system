/**
 * File:    UidTest.cpp
 * Purpose: Tests for Uid class.
 * Creator: Brendan College
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Uid.hpp"

namespace fms {

TEST(UidTest, Seed)
{
    std::string uid0 = Uid::generate();
    std::string uid1 = Uid::generate();

    EXPECT_EQ(uid0.length(), Uid::UID_LENGTH);
    EXPECT_EQ(uid1.length(), Uid::UID_LENGTH);

    EXPECT_STRNE(uid0.c_str(), "");
    EXPECT_STRNE(uid0.c_str(), uid1.c_str());

    uid0 = Uid::generate("seed1");
    EXPECT_STRNE(uid0.c_str(), uid1.c_str());

    uid1 = Uid::generate("seed1");
    EXPECT_STREQ(uid0.c_str(), uid1.c_str());

    uid0 = Uid::generate("seed2");
    EXPECT_STRNE(uid0.c_str(), uid1.c_str());

    uid1 = Uid::generate("seed2");
    EXPECT_STREQ(uid0.c_str(), uid1.c_str());
}

} // namespace fms