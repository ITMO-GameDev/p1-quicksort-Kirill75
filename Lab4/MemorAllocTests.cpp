#include "pch.h"
#include "MemorAlloc.h"

class MemoryAllocatorTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        allocator.init();
    }

    void TearDown() override
    {
        allocator.free(ptr);
    }

    MemoryAllocator allocator;
    void* ptr = nullptr;
};

TEST(MemoryAllocatorTests, NullAllocation)
{
	void* p = allocator.alloc(0);

	ASSERT_EQ(p, nullptr);
}

TEST(MemoryAllocatorTests, FsaAllocationTest)
{
	void* p = allocator.alloc(sizeof(int));

	ASSERT_NE(p, nullptr);
	ASSERT_EQ((uintptr_t)p % 8, 0);
}

TEST(MemoryAllocatorTests, CoalesceAllocationTest)
{
	void* p = allocator.alloc(10000 * sizeof(int));

	ASSERT_NE(p, nullptr);
	ASSERT_EQ((uintptr_t)p % 8, 0);
}

TEST(MemoryAllocatorTests, LargeAllocationTest)
{
	void* p = allocator.alloc(11 * 1024 * 1024);

	ASSERT_NE(p, nullptr);
	ASSERT_EQ((uintptr_t)p % 8, 0);