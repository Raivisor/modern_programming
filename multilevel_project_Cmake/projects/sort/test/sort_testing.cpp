#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "shellSorting.hpp"

TEST(ArrayEquals, AssertEqual) {
	int actual[] = {9, 8, 7, 6, 5, 25, 5, 7, 3, 234};

	const int size = sizeof(actual) / sizeof(actual[0]);

	int expected[] = {3, 5, 5, 6, 7, 7, 8, 9, 25, 234};

	mogger::sorting::shellSorting(std::begin(actual), std::end(actual));
    //либо mergeSort(actual, actual + size)
    //либо mergoSort(&actual[0], &actual[size])

	for (int i = 0; i < size; i++) {
		ASSERT_EQ(actual[i],expected[i]) 
			<< "Массив actual отличается от expected в индексе: "
			<< i;
	}
}


int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}