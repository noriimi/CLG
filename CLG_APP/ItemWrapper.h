#pragma once
#include "Item.h"
#include <cmath>
class ItemWrapper
{
public:
	Item item;
	ItemWrapper* parent = nullptr;
	ItemWrapper* parentB = nullptr;
	bool collision;
	bool col;
	int level = -1;
	void coll();
	ItemWrapper();
	ItemWrapper(ItemWrapper* _parent, Item _item);
	ItemWrapper(Item _item);
	ItemWrapper(Item _item, ItemWrapper* _parent, ItemWrapper* _parentB);
	friend bool operator==(const ItemWrapper& lhs, const ItemWrapper& rhs)
	{
		return lhs.item == rhs.item && lhs.collision == rhs.collision && lhs.col == rhs.col;
	}
	size_t operator()(const ItemWrapper& rhs) const {
		size_t hash = std::abs((rhs.item.bottomRight.x - rhs.item.topLeft.x) * (rhs.item.bottomRight.y - rhs.item.topLeft.y));
		return hash;
	}

};

