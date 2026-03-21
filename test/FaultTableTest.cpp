/**
 * File:    FaultTableTest.cpp
 * Purpose: Tests for FaultTable class.
 * Creator: Brendan College
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define private public
#include "FaultTable.hpp"
#undef private

namespace fms {

TEST(FaultTableTest, Initialization)
{
    FaultTable table;
    bool allFaultStatusUninit = true;
    bool allFaultGroupEmpty = true;
    bool allUidEmpty = true;

    for (FaultTableEntry& entry: table.faultTable_)
    {
        if (entry.faultStatus_ != Status::UNINITIALIZED)
        {
            allFaultStatusUninit = false;
        }
        if (entry.faultGroup_ != "")
        {
            allFaultGroupEmpty = false;
        }
        if (entry.uid_ != "")
        {
            allUidEmpty = false;
        }
    }

    EXPECT_TRUE(allFaultStatusUninit);
    EXPECT_TRUE(allFaultGroupEmpty);
    EXPECT_TRUE(allUidEmpty);
}

TEST(FaultTableTest, AddFault)
{
    FaultTable table;
    FaultTableEntry entry(Status::PASS);

    EXPECT_EQ(table.faultTable_[0].faultStatus_, Status::UNINITIALIZED);
    EXPECT_TRUE(table.faultTable_[0].uid_.empty());

    EXPECT_TRUE(table.addFault(entry));

    EXPECT_EQ(table.faultTable_[0].faultStatus_, Status::PASS);
    EXPECT_FALSE(table.faultTable_[0].uid_.empty());
}

TEST(FaultTableTest, GetFaultStatus)
{
    FaultTable table;
    FaultTableEntry entry(
        Status::PASS,
        std::string("groupA"),
        std::string("deadbeef")
    );
    Status status = Status::UNINITIALIZED;

    EXPECT_TRUE(table.addFault(entry));
    EXPECT_TRUE(table.getFaultStatus(std::string("deadbeef"), status));
    EXPECT_EQ(status, Status::PASS);

    EXPECT_FALSE(table.getFaultStatus(std::string("feedc0de"), status));
    EXPECT_EQ(status, Status::PASS);
}

} // namespace fms