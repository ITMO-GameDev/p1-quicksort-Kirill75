#include "pch.h"
#include "Contain.h"


TEST(ContainTests, initTest) {
	Array<int> d;
	EXPECT_TRUE(d.size()==0);
	EXPECT_TRUE(d.capacity() == 8);

	Array<int> c(42);
	EXPECT_TRUE(c.size() == 0);
	EXPECT_TRUE(c.capacity() == 42);
}

TEST(ContainTests, insertTest) {
	Array<int> d;
	d.insert(5);
	d.insert(5);
	d.insert(0 , 4);
	d.insert(3, 15);
	EXPECT_TRUE(d[0] == 4);
	EXPECT_TRUE(d[1] == 5);
	EXPECT_TRUE(d[3] == 15);
	EXPECT_TRUE(d.size() == 4);
	ASSERT_ANY_THROW(d.insert(125, 5));
}

TEST(ContainTests, test) {
	Array<int> a;
	for (int i = 0; i < 1110; ++i)
		a.insert(i);
	for (int i = 0; i < a.size(); ++i)
		a[i] *= 2;
	for (int i = 0; i < a.size(); ++i)
		EXPECT_TRUE(a[i] == i * 2);
}

TEST(ContainTests, iteratorInitTest) {
	Array<int> a;
	for (int i = 0; i < 3; ++i)
		a.insert(i);
	auto it = a.iterator();
	EXPECT_TRUE(it.get() == 0);
	EXPECT_FALSE(it.hasPrev());
	
}
TEST(ContainTests, iteratorForwardMoveTest) {
	Array<int> a;
	for (int i = 0; i < 3; ++i)
		a.insert(i);
	auto it = a.iterator();
	it.next();
	EXPECT_TRUE(it.get() == 1);
	it.next();
	EXPECT_TRUE(it.get() == 2);
	EXPECT_FALSE(it.hasNext());
}

TEST(ContainTests, iteratorSetTest) {
	Array<int> a;
	for (int i = 0; i < 3; ++i)
		a.insert(i);
	auto it = a.iterator();
	it.set(5);
	EXPECT_TRUE(it.get() == 5);
	EXPECT_TRUE(a.size() == 3);
}

}
TEST(ContainTests, iteratorToIndexTest) {
	Array<int> a;
	for (int i = 0; i < 3; ++i)
		a.insert(i);
	auto it = a.iterator();
	it.toIndex(2);
	EXPECT_TRUE(it.get() == 2);
}