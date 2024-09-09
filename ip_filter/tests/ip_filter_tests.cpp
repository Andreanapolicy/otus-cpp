#include <gtest/gtest.h>
#include "../src/ip_list.h"
#include <sstream>

TEST(IPList, EmptyListAfterCreating)
{
    ip_address::IPList ipList;
    EXPECT_EQ(ipList.Empty(), true);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}