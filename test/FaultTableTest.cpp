/**
 * File:    FaultTableTest.cpp
 * Purpose: Tests for FaultTable class.
 * Creator: Brendan College
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FaultTable.hpp"

namespace fms {

TEST(FaultTableTest, AddFault)
{
    FaultTable table;
    FaultTableEntry entry(Status::PASS, "group_a");

    EXPECT_TRUE(table.addFault(entry));
}

TEST(FaultTableTest, RemoveFault)
{
    FaultTable table;
    FaultTableEntry entry(Status::PASS, "group_a");
    table.addFault(entry);

    EXPECT_TRUE(table.removeFault(entry.getUid()));
    EXPECT_FALSE(table.removeFault(entry.getUid()));
}

} // namespace fms