#include <iostream>
#include "../Map/map.hpp"
#include "gtest/gtest.h"

TEST(Simple, Test) {
    EXPECT_TRUE(true);

}
TEST(Map, defaultconstruct) {
    map1::Map map;
    EXPECT_EQ(map.get_max_y(),0);
    EXPECT_EQ(map.get_max_x(),0);
    EXPECT_EQ(map.get_hp(),0);
    EXPECT_EQ(map.get_money(),0);
    EXPECT_EQ(map.get_towers().size(),0);
    EXPECT_EQ(map.get_enemies().size(),0);
}
TEST(Map, construct) {
    map1::Map map(15,15);
    EXPECT_EQ(map.get_max_y(),15);
    EXPECT_EQ(map.get_max_x(),15);
    EXPECT_EQ(map.get_hp(),10000);
    EXPECT_EQ(map.get_money(),1000);
    EXPECT_EQ(map.get_towers().size(),0);
    EXPECT_EQ(map.get_enemies().size(),0);
}

