#include "ItemWrapper.h"

void ItemWrapper::coll()
{
	collision = true;
}

ItemWrapper::ItemWrapper() :parent{ nullptr }, item{ Item() }, level{ 0 }, collision{ false }, col{ false }
{
}
ItemWrapper::ItemWrapper(ItemWrapper* _parent, Item _item) :collision{ false }, col{ false }
{
	parent = _parent;
	item = _item;
}
ItemWrapper::ItemWrapper(Item _item) :collision{ false }, col{ false }
{
	item = _item;
}

ItemWrapper::ItemWrapper(Item _item, ItemWrapper* _parent, ItemWrapper* _parentB)
{
	parent = _parent;
	item = _item;
	parentB = _parentB;
}
