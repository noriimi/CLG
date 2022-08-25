#include "Item.h"
#include <algorithm>
#include "imgui.h"
#include "ColorsID.h"
void Item::convert()
{
	start.x = 10 * roundf(start.x / 10);
	start.y = 10 * roundf(start.y / 10);
	end.x = 10 * roundf(end.x / 10);
	end.y = 10 * roundf(end.y / 10);
}
float Item::area()
{
	return abs((end.x - start.x) * (end.y - start.y));
}

void Item::calculate()
{
	ImVec2 temp[4] = { start, end, { end.x,start.y }, { start.x,end.y } };
	std::sort(temp, temp + 4, [](ImVec2 i, ImVec2 j) {return (i.x < j.x); });
	std::sort(temp, temp + 2, [](ImVec2 i, ImVec2 j) {return (i.y < j.y); });
	std::sort(temp + 2, temp + 4, [](ImVec2 i, ImVec2 j) {return (i.y < j.y); });
	topLeft = temp[0];
	bottomRight = temp[3];
	calculateDiagonal();
}
Item::Item() :id{ -1 }, color{ RED } {

}

void Item::calculateDiagonal()
{
	one = { (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x), bottomRight.y - (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x) * bottomRight.x };
	two = { -(bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x), topLeft.y + (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x) * bottomRight.x };
}
