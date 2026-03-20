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

TEST(FaultTableTest, AddRemoveFault)
{
    FaultTable table;
    FaultTableEntry entry(Status::PASS);

    EXPECT_TRUE(table.addFault(entry));
    EXPECT_TRUE(table.removeFault(entry.getUid()));
    EXPECT_FALSE(table.removeFault(entry.getUid()));
}

} // namespace fms