#include "pch.h"
#include "qSort.h"


namespace tests {
	template<typename T, typename Compare>
	bool isSorted(T* start, T* end, Compare comp) {
		
			while (start < end) {
				if (comp (*(start + 1), *start)) {
					return false;
				}
				start++;
		}
		return true;
	}
	TEST(qSortTests, commonIntSortTest) {

		int a[] = { 2,3,3,3,8,4,1,1,2,3,5 };

		quick_sort(a, a + (std::size(a) - 1), [](int a, int b) {return a < b; });

		EXPECT_TRUE(isSorted(a, a + (std::size(a) - 1), [](int a, int b) {return a < b; }));
		

	}

	TEST(qSortTests, reverseIntSort) {

		int a[] = { 55,52,52,51,49,45,43,43,42,32,31,30,25,24,23,22,18,16,10,4,1,-3,-5 };
		quick_sort(a, a + (std::size(a) - 1), [](int a, int b) {return a < b; });
		EXPECT_TRUE(isSorted(a, a + (std::size(a) - 1), [](int a, int b) {return a < b; }));

	}

	TEST(qSortTests, repeatableIntSort) {

		int a[] = { 2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5 };
		quick_sort(a, a + (std::size(a) - 1), [](int a, int b) {return a < b; });
		EXPECT_TRUE(isSorted(a, a + (std::size(a) - 1), [](int a, int b) {return a < b; }));

	}
}
