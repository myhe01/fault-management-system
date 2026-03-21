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
    bool allFaultGroupsEmpty = true;
    bool allUidEmpty = true;

    for (FaultTableEntry& entry: table.faultTable_)
    {
        if (entry.faultStatus_ != Status::UNINITIALIZED)
        {
            allFaultStatusUninit = false;
        }
        if (!entry.faultGroups_.empty())
        {
            allFaultGroupsEmpty = false;
        }
        if (entry.uid_ != "")
        {
            allUidEmpty = false;
        }
    }

    EXPECT_TRUE(allFaultStatusUninit);
    EXPECT_TRUE(allFaultGroupsEmpty);
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

    EXPECT_TRUE(table.addFault(Status::FAIL));

    EXPECT_EQ(table.faultTable_[1].faultStatus_, Status::FAIL);
    EXPECT_FALSE(table.faultTable_[1].uid_.empty());
}

TEST(FaultTableTest, AddFaultMax)
{
    FaultTable table;

    for (std::size_t i = 0; i < FaultTable::MAX_FAULT_TABLE_ENTRIES_; i++)
    {
        EXPECT_TRUE(table.addFault(Status::PASS, std::to_string(i)));
    }

    EXPECT_FALSE(table.addFault(Status::PASS, std::to_string(FaultTable::MAX_FAULT_TABLE_ENTRIES_)));
}

TEST(FaultTableTest, GetFaultStatus)
{
    FaultTable table;
    FaultTableEntry entry(
        Status::PASS,
        std::string("deadbeef")
    );
    Status status = Status::UNINITIALIZED;

    EXPECT_TRUE(table.addFault(entry));
    EXPECT_TRUE(table.getFaultStatus(std::string("deadbeef"), status));
    EXPECT_EQ(status, Status::PASS);

    EXPECT_FALSE(table.getFaultStatus(std::string("feedc0de"), status));
    EXPECT_EQ(status, Status::PASS);
}

TEST(FaultTableTest, AssignFaultGroup)
{
    FaultTable table;
    FaultTableEntry entry0(
        Status::PASS,
        std::string("deadbeef")
    );

    EXPECT_TRUE(table.addFault(entry0));
    EXPECT_STREQ(table.faultTable_[0].uid_.c_str(), "deadbeef");
    EXPECT_FALSE(table.faultTable_[0].inFaultGroup(1));

    EXPECT_TRUE(table.assignFaultGroup(std::string("deadbeef"), 1));
    EXPECT_TRUE(table.faultTable_[0].inFaultGroup(1));

    EXPECT_TRUE(table.assignFaultGroup(std::string("deadbeef"), 67));
    EXPECT_TRUE(table.faultTable_[0].inFaultGroup(1));
    EXPECT_TRUE(table.faultTable_[0].inFaultGroup(67));

    FaultTableEntry entry1(
        Status::FAIL,
        std::string("feedc0de")
    );

    EXPECT_TRUE(table.addFault(entry1));
    EXPECT_STREQ(table.faultTable_[1].uid_.c_str(), "feedc0de");
    EXPECT_FALSE(table.faultTable_[1].inFaultGroup(1));

    EXPECT_TRUE(table.assignFaultGroup(std::string("feedc0de"), 2));
    EXPECT_TRUE(table.faultTable_[0].inFaultGroup(1));
    EXPECT_FALSE(table.faultTable_[0].inFaultGroup(2));
    EXPECT_TRUE(table.faultTable_[0].inFaultGroup(67));
    EXPECT_FALSE(table.faultTable_[1].inFaultGroup(1));
    EXPECT_TRUE(table.faultTable_[1].inFaultGroup(2));
    EXPECT_FALSE(table.faultTable_[1].inFaultGroup(67));
}

TEST(FaultTableTest, GetGroupStatus)
{
    FaultTable table;
    FaultTableEntry entry0(
        Status::PASS,
        std::string("deadbeef")
    );
    FaultTableEntry entry1(
        Status::FAIL,
        std::string("feedc0de")
    );
    FaultTableEntry entry2(
        Status::FAIL,
        std::string("cafebabe")
    );

    EXPECT_TRUE(table.addFault(entry0));
    EXPECT_TRUE(table.addFault(entry1));
    EXPECT_TRUE(table.addFault(entry2));

    EXPECT_TRUE(table.assignFaultGroup(std::string("deadbeef"), 1));
    EXPECT_TRUE(table.faultTable_[0].inFaultGroup(1));
    EXPECT_EQ(table.getGroupStatus(1), Status::PASS);

    EXPECT_TRUE(table.assignFaultGroup(std::string("feedc0de"), 2));
    EXPECT_FALSE(table.faultTable_[0].inFaultGroup(2));
    EXPECT_TRUE(table.faultTable_[1].inFaultGroup(2));
    EXPECT_EQ(table.getGroupStatus(1), Status::PASS);
    EXPECT_EQ(table.getGroupStatus(2), Status::FAIL);

    EXPECT_TRUE(table.assignFaultGroup(std::string("cafebabe"), 1));
    EXPECT_TRUE(table.faultTable_[2].inFaultGroup(1));
    EXPECT_EQ(table.getGroupStatus(1), Status::FAIL);
}

TEST(FaultTableTest, GivenExampleUseCase)
{
    FaultTable table;

    EXPECT_TRUE(table.addFault(Status::UNINITIALIZED, std::string("fault1")));
    EXPECT_TRUE(table.addFault(Status::UNINITIALIZED, std::string("fault2")));
    EXPECT_TRUE(table.addFault(Status::UNINITIALIZED, std::string("fault3")));

    EXPECT_TRUE(table.assignFaultGroup(std::string("fault1"), 0xa));
    EXPECT_TRUE(table.assignFaultGroup(std::string("fault2"), 0xa));
    EXPECT_TRUE(table.assignFaultGroup(std::string("fault3"), 0xb));

    EXPECT_TRUE(table.setFaultStatus(std::string("fault1"), Status::PASS));
    EXPECT_TRUE(table.setFaultStatus(std::string("fault2"), Status::FAIL));

    EXPECT_EQ(table.getGroupStatus(0xa), Status::FAIL);

    EXPECT_TRUE(table.setFaultStatus(std::string("fault2"), Status::PASS));

    EXPECT_EQ(table.getGroupStatus(0xa), Status::PASS);
}

} // namespace fms