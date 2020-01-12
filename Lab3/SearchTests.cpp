#include "pch.h"
#include "Search.h"

TEST(SearchTest, initTest)
{
	Dictionary<std::string, int> npc;
	EXPECT_TRUE(npc.size()==0);
	
}
TEST(SearchTest, putTest)
{
	Dictionary<std::string, int> npc;
	for(auto i=0;i<10;i++)
	{
		npc.put(std::to_string(i), i);
	}
	
	EXPECT_TRUE(npc.size() == 10);

}
TEST(SearchTest, containsTest)
{
	Dictionary<std::string, int> npc;
	for (auto i = 0; i < 10; i++)
	{
		npc.put(std::to_string(i), i);
	}
	for (auto i = 0; i < 10; i++)
	{
		EXPECT_TRUE(npc.contains(std::to_string(i)));
	}
	EXPECT_TRUE(npc.size() == 10);

}
TEST(SearchTest, removeTest)
{
	Dictionary<std::string, int> npc;
	for (auto i = 0; i < 10; i++)
	{
		npc.put(std::to_string(i), i);
	}
	for (auto i = 0; i < 5; i++)
	{
		npc.remove(std::to_string(i));
	}
	for (auto i = 0; i < 5; i++)
	{
		EXPECT_FALSE(npc.contains(std::to_string(i)));
	}
	for (auto i = 5; i < 10; i++)
	{
		EXPECT_TRUE(npc.contains(std::to_string(i)));
	}
	EXPECT_TRUE(npc.size() == 5);

}

