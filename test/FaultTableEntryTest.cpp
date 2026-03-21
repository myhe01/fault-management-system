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
    EXPECT_TRUE(entry0.faultGroups_.empty());
    EXPECT_STREQ(entry0.uid_.c_str(), "");

    FaultTableEntry entry1(Status::FAIL);
    EXPECT_EQ(entry1.faultStatus_, Status::FAIL);
    EXPECT_TRUE(entry1.faultGroups_.empty());
    EXPECT_STRNE(entry1.uid_.c_str(), "");

    FaultTableEntry entry2(Status::FAIL, std::string("deadbeef"));
    EXPECT_EQ(entry2.faultStatus_, Status::FAIL);
    EXPECT_TRUE(entry2.faultGroups_.empty());
    EXPECT_STREQ(entry2.uid_.c_str(), "deadbeef");
}

TEST(FaultTableEntryTest, Getters)
{
    FaultTableEntry entry(Status::PASS, std::string("baddcafe"));

    EXPECT_EQ(entry.getFaultStatus(), Status::PASS);
    EXPECT_STREQ(entry.getUid().c_str(), "baddcafe");
}

TEST(FaultTableEntryTest, Setters)
{
    FaultTableEntry entry;

    EXPECT_EQ(entry.getFaultStatus(), Status::UNINITIALIZED);
    EXPECT_STREQ(entry.getUid().c_str(), "");

    entry.setFaultStatus(Status::FAIL);
    EXPECT_EQ(entry.getFaultStatus(), Status::FAIL);
    EXPECT_STRNE(entry.getUid().c_str(), "");
}

TEST(FaultTableEntryTest, AssignFaultGroupInFaultGroup)
{
    FaultTableEntry entry;

    EXPECT_TRUE(entry.faultGroups_.empty());

    entry.assignFaultGroup(1);
    EXPECT_TRUE(entry.inFaultGroup(1));
    EXPECT_EQ(entry.faultGroups_.size(), 1);
    EXPECT_STRNE(entry.getUid().c_str(), "");

    entry.assignFaultGroup(2);
    EXPECT_TRUE(entry.inFaultGroup(2));
    EXPECT_EQ(entry.faultGroups_.size(), 2);

    for (int i = 0; i < 5; i++)
    {
        entry.assignFaultGroup(42);
    }
    EXPECT_TRUE(entry.inFaultGroup(42));
    EXPECT_EQ(entry.faultGroups_.count(42), 1);
    EXPECT_EQ(entry.faultGroups_.size(), 3);
}

TEST(FaultTableEntryTest, FillUid)
{
    FaultTableEntry entry;

    EXPECT_TRUE(entry.uid_.empty());
    entry.fillUidIfEmpty_();
    EXPECT_FALSE(entry.uid_.empty());
    entry.fillUidIfEmpty_();
}

} // namespace fms