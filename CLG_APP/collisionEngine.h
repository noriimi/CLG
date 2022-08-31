#pragma once
#include <algorithm>
#include <unordered_set>
#include "ItemWrapper.h"
namespace std {
	template<> struct hash<Item>
	{
		std::size_t operator()(const Item& p) const noexcept
		{
			return p(p);
		}
	};
	template<> struct hash<ItemWrapper>
	{
		std::size_t operator()(const ItemWrapper& p) const noexcept
		{
			return p(p);
		}
	};
}
class collisionEngine
{
private:
	std::unordered_set<ItemWrapper> input;
	std::vector<ItemWrapper> collisions;
    bool doOverlap(ImVec2 l1, ImVec2 r1, ImVec2 l2, ImVec2 r2);
    Item calcOverlap(Item a, Item b);
    bool doOverlap(Item a, Item b);
	int id = 0;
	std::vector<ItemWrapper> in, out;
	int doStuff();
public:
    collisionEngine()=default;
    collisionEngine(std::vector<Item>& v);
    std::vector<ItemWrapper> getCollisions();
    std::vector<ItemWrapper> getRest();
    int run();
};

