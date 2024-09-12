#include <gtest/gtest.h>
#include "../src/ip_list.h"
#include <sstream>

class IPListTest : public testing::Test
{
protected:
    IPListTest() = default;
    
    ~IPListTest() override = default;
    
    void SetUp() override
    {    
        std::ostringstream oss;
        oss << "10.10.10.10\t2\t4" << std::endl;
        oss << "2.2.100.30\t2\t4" << std::endl;
        oss << "1.2.100.30\t2\t4" << std::endl;
        oss << "46.70.100.30\t2\t4" << std::endl;
        oss << "46.1.100.30\t2\t4" << std::endl;
        
        std::istringstream iss(oss.str());
        iss >> ipList;
    }
    
    void TearDown() override {}

    ip_address::IPList ipList;
};


TEST(IPList, EmptyListAfterCreating)
{
    ip_address::IPList ipList;
    ASSERT_FALSE(ipList.Empty());
}

TEST(IPList, TestReadFromStream)
{
    ip_address::IPList ipList;
    std::istringstream iss("10.10.10.10\t2\t4\n2.2.100.30\t2\t4");

    iss >> ipList;

    ASSERT_FALSE(ipList.Empty());
    ASSERT_EQ(ipList.Count(), 2);
}

TEST_F(IPListTest, TestWriteToStream)
{
    std::ostringstream oss;
    
    oss << ipList;

    ASSERT_EQ(oss.str(), "10.10.10.10\n2.2.100.30\n1.2.100.30\n46.70.100.30\n46.1.100.30\n");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}