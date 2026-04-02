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

// ----------------------------------------------------------
// PRINT
// ----------------------------------------------------------

TEST(DoublyLinkedListPrintTest, PrintEmptyList) {
    DoublyLinkedList<int> list;
    
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "\n");
}

TEST(DoublyLinkedListPrintTest, PrintSingleElement) {
    DoublyLinkedList<int> list;
    list.push_back(42);
    
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "42 \n");
}

TEST(DoublyLinkedListPrintTest, PrintMultipleElements) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "10 20 30 \n");
}

TEST(DoublyLinkedListPrintTest, PrintWithStrings) {
    DoublyLinkedList<std::string> list;
    list.push_back("apple");
    list.push_back("banana");
    list.push_back("cherry");
    
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "apple banana cherry \n");
}

// ----------------------------------------------------------
// REMOVE FIRST
// ----------------------------------------------------------

TEST(DoublyLinkedListRemoveFirstTest, RemoveOnlyElement) {
    DoublyLinkedList<int> list;
    list.push_back(42);
    
    EXPECT_TRUE(list.remove_first(42));
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_FALSE(list.has_item(42));
}

TEST(DoublyLinkedListRemoveFirstTest, RemoveFirstElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
    EXPECT_TRUE(list.has_item(30));
}

TEST(DoublyLinkedListRemoveFirstTest, RemoveMiddleElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(20));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(list.has_item(10));
    EXPECT_FALSE(list.has_item(20));
    EXPECT_TRUE(list.has_item(30));
}

TEST(DoublyLinkedListRemoveFirstTest, RemoveLastElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(30));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
    EXPECT_FALSE(list.has_item(30));
}