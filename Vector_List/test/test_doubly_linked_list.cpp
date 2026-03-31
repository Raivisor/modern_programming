#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using mogger::DoublyLinkedList;

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// ----------------------------------------------------------
// PUSH BACK
// ----------------------------------------------------------

TEST(DoublyLinkedListPushBackTest, PushBackIntoEmptyList) {
    DoublyLinkedList<int> list;
    
    list.push_back(42);
    
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_TRUE(list.has_item(42));
}

TEST(DoublyLinkedListPushBackTest, PushBackMultipleElements) {
    DoublyLinkedList<int> list;
    
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
    EXPECT_TRUE(list.has_item(30));
}

TEST(DoublyLinkedListPushBackTest, PushBackWithStrings) {
    DoublyLinkedList<std::string> list;
    
    list.push_back("apple");
    list.push_back("banana");
    list.push_back("cherry");
    
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item("apple"));
    EXPECT_TRUE(list.has_item("banana"));
    EXPECT_TRUE(list.has_item("cherry"));
}

TEST(DoublyLinkedListPushBackTest, PushBackManyElements) {
    DoublyLinkedList<int> list;
    
    for(int i = 0; i < 100; ++i) {
        list.push_back(i);
    }
    
    EXPECT_EQ(list.get_size(), 100);
    
    for(int i = 0; i < 100; ++i) {
        EXPECT_TRUE(list.has_item(i));
    }
}