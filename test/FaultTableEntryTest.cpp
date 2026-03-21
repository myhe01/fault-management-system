/**
 * File:    FaultTableEntryTest.cpp
 * Purpose: Tests for FaultTableEntry class.
 * Creator: Brendan College
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define private public
#include "FaultTableEntry.hpp"
#undef private

namespace fms {

TEST(FaultTableEntryTest, Initialization)
{
    FaultTableEntry entry0;
    EXPECT_EQ(entry0.faultStatus_, Status::UNINITIALIZED);
    EXPECT_STREQ(entry0.faultGroup_.c_str(), "");
    EXPECT_STREQ(entry0.uid_.c_str(), "");

    FaultTableEntry entry1(Status::FAIL);
    EXPECT_EQ(entry1.faultStatus_, Status::FAIL);
    EXPECT_STREQ(entry1.faultGroup_.c_str(), "");
    EXPECT_STRNE(entry1.uid_.c_str(), "");

    FaultTableEntry entry2(Status::FAIL, std::string("groupA"), std::string("deadbeef"));
    EXPECT_EQ(entry2.faultStatus_, Status::FAIL);
    EXPECT_STREQ(entry2.faultGroup_.c_str(), "groupA");
    EXPECT_STREQ(entry2.uid_.c_str(), "deadbeef");
}

TEST(FaultTableEntryTest, Getters)
{
    FaultTableEntry entry(Status::PASS, std::string("groupB"), std::string("baddcafe"));

    EXPECT_EQ(entry.getFaultStatus(), Status::PASS);
    EXPECT_STREQ(entry.getFaultGroup().c_str(), "groupB");
    EXPECT_STREQ(entry.getUid().c_str(), "baddcafe");
}

TEST(FaultTableEntryTest, Setters)
{
    FaultTableEntry entry;
    entry.setFaultStatus(Status::FAIL);
    entry.setFaultGroup(std::string("groupC"));

    EXPECT_EQ(entry.getFaultStatus(), Status::FAIL);
    EXPECT_STREQ(entry.getFaultGroup().c_str(), "groupC");
    EXPECT_STRNE(entry.getUid().c_str(), "");
}

TEST(FaultTableEntryTest, FillUid)
{
    FaultTableEntry entry;

    EXPECT_TRUE(entry.uid_.empty());
    entry.fillUid_();
    EXPECT_FALSE(entry.uid_.empty());
    entry.fillUid_();
}

} // namespace fms