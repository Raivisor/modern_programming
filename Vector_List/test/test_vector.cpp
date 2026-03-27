#include <gtest/gtest.h>

#include "vector.hpp"

using mogger::Vector;

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


TEST(VectorConstructorTest, DefaultConstructor) {
	Vector<int> x;

	EXPECT_EQ(x.get_size(), 0);
}

TEST(VectorPushBackTest, SizeOneAndStore) {
    Vector<int> v;
    v.push_back(42);
    
    EXPECT_EQ(v.get_size(), 1);
	EXPECT_TRUE(v.has_item(42));
    EXPECT_FALSE(v.has_item(99));
}

TEST(VectorPushBackTest, IncreaseSizeAndStore) {
    Vector<int> v;
    
    v.push_back(10);
    EXPECT_EQ(v.get_size(), 1);
    
    v.push_back(20);
    EXPECT_EQ(v.get_size(), 2);
    
    v.push_back(30);
    EXPECT_EQ(v.get_size(), 3);

	EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorPushBackTest, PushBackWithDifferentTypes) {
    Vector<double> v_double;
    v_double.push_back(3.14);
    v_double.push_back(2.718);
    
    EXPECT_EQ(v_double.get_size(), 2);
    EXPECT_TRUE(v_double.has_item(3.14));
    EXPECT_TRUE(v_double.has_item(2.718));
    
    Vector<std::string> v_string;
    v_string.push_back("hello");
    v_string.push_back("world");
    
    EXPECT_EQ(v_string.get_size(), 2);
    EXPECT_TRUE(v_string.has_item("hello"));
    EXPECT_TRUE(v_string.has_item("world"));
}

TEST(VectorPushBackTest, PushBackBeyondInitialCapacity) {
    Vector<int> v;
    for(int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    
    EXPECT_EQ(v.get_size(), 100);
    
    for(int i = 0; i < 100; ++i) {
        EXPECT_TRUE(v.has_item(i));
    }
}