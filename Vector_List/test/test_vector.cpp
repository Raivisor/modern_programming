#include <gtest/gtest.h>

#include "vector.hpp"

using mogger::Vector;

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// ----------------------------------------------------------
// CONSTRUCTOR
// ----------------------------------------------------------

TEST(VectorConstructorTest, DefaultConstructor) {
	Vector<int> x;

	EXPECT_EQ(x.get_size(), 0);
}

// ----------------------------------------------------------
// INSERT
// ----------------------------------------------------------

TEST(VectorTest, InsertAtBeginning) {
    Vector<int> v;
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.insert(0, 10));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorTest, InsertAtMiddle) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(30);
    
    EXPECT_TRUE(v.insert(1, 20));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorTest, InsertAtEnd) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_TRUE(v.insert(2, 30));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorTest, InsertInvalidPosition) {
    Vector<int> v;
    v.push_back(10);
    
    EXPECT_FALSE(v.insert(5, 20));
    EXPECT_EQ(v.get_size(), 1);
}

// ----------------------------------------------------------
// PUSH BACK
// ----------------------------------------------------------

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

// ----------------------------------------------------------
// REMOVE FIRST
// ----------------------------------------------------------

TEST(VectorRemoveFirstTest, RemoveExistingElement) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(30));
    EXPECT_FALSE(v.has_item(20));
}

TEST(VectorRemoveFirstTest, RemoveFirstElement) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(10));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
    EXPECT_FALSE(v.has_item(10));
}

TEST(VectorRemoveFirstTest, RemoveLastElement) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(30));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_FALSE(v.has_item(30));
}

TEST(VectorRemoveFirstTest, RemoveOnlyElement) {
    Vector<int> v;
    v.push_back(42);
    
    EXPECT_TRUE(v.remove_first(42));
    EXPECT_EQ(v.get_size(), 0);
    EXPECT_FALSE(v.has_item(42));
}

TEST(VectorRemoveFirstTest, RemoveNonExistingElement) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_FALSE(v.remove_first(99));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
}

TEST(VectorRemoveFirstTest, RemoveFromEmptyVector) {
    Vector<int> v;
    
    EXPECT_FALSE(v.remove_first(42));
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorRemoveFirstTest, RemoveFirstDuplicate) {
    Vector<int> v;
    v.push_back(20);
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorRemoveFirstTest, RemoveWithString) {
    Vector<std::string> v;
    v.push_back("apple");
    v.push_back("banana");
    v.push_back("cherry");
    
    EXPECT_TRUE(v.remove_first("banana"));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item("apple"));
    EXPECT_TRUE(v.has_item("cherry"));
    EXPECT_FALSE(v.has_item("banana"));
}

TEST(VectorRemoveFirstTest, RemoveAfterShrink) {
    Vector<int> v;
    
    for(int i = 0; i < 50; ++i) {
        v.push_back(i);
    }
    EXPECT_EQ(v.get_size(), 50);
    
    for(int i = 0; i < 40; ++i) {
        EXPECT_TRUE(v.remove_first(i));
    }
    EXPECT_EQ(v.get_size(), 10);
    EXPECT_TRUE(v.has_item(40));
    EXPECT_TRUE(v.has_item(49));
}