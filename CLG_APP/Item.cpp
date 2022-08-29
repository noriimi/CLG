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
float Item::area() const
{
	return abs((end.x - start.x) * (end.y - start.y));
}
float Item::area2()
{
	return abs((bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y));
}
bool Item::operator<(const Item& rhs)
{
	return color<rhs.color;
}
void Item::calculate()
{
	ImVec2 temp[4] = { start, end, { end.x,start.y }, { start.x,end.y } };
	std::sort(temp, temp + 4, [](ImVec2 i, ImVec2 j) {return (i.x < j.x); });
	std::sort(temp, temp + 2, [](ImVec2 i, ImVec2 j) {return (i.y < j.y); });
	std::sort(temp + 2, temp + 4, [](ImVec2 i, ImVec2 j) {return (i.y < j.y); });
	topLeft = temp[0];
	bottomRight = temp[3];
	//topLeft = start;
	//bottomRight = end;
	topRight = { bottomRight.x,topLeft.y };
	bottomLeft = { topLeft.x ,bottomRight.y };
	calculateDiagonal();
}
Item::Item() :id{ -1 }, color{ RED } {

}

Item::Item(ImVec2 start_, ImVec2 end_, ColorsID color_):start{start_},end{end_},color{color_},id{-1}
{
	//convert();
	calculate();
}

void Item::calculateDiagonal()
{
	one = { (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x), bottomRight.y - (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x) * bottomRight.x };
	two = { -(bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x), topLeft.y + (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x) * bottomRight.x };
}
bool operator==(const Item& lhs, const Item& rhs)
{
    return lhs.topLeft.x == rhs.topLeft.x && lhs.topLeft.y == rhs.topLeft.y && lhs.bottomRight.x == rhs.bottomRight.x && lhs.bottomRight.y == rhs.bottomRight.y && rhs.color == lhs.color;
}
std::ostream& operator<<(std::ostream& os, const Item& obj)
{
	return os << obj.topLeft.x << '\t' << obj.topLeft.y << '\t' << obj.bottomRight.x << '\t' << obj.bottomRight.y << '\t' << obj.color << '\t' << std::abs((obj.bottomRight.x - obj.topLeft.x) * (obj.bottomRight.y - obj.topLeft.y));
}