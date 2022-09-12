#include "Item.h"
#include <algorithm>
#include "imgui.h"
#include "ColorsID.h"
void item::convert()
{
	start.x = 10 * roundf(start.x / 10);
	start.y = 10 * roundf(start.y / 10);
	end.x = 10 * roundf(end.x / 10);
	end.y = 10 * roundf(end.y / 10);
}
float item::area() const
{
	if (start.x > end.x || start.y > end.y)
		return 0;
	return abs((end.x - start.x) * (end.y - start.y));
}
float item::area2() const
{
	return abs((bottom_right.x - top_left.x) * (bottom_right.y - top_left.y));
}
bool item::operator<(const item& rhs) const
{
	return color<rhs.color;
}
void item::calculate()
{
	ImVec2 temp[4] = { start, end, { end.x,start.y }, { start.x,end.y } };
	std::sort(temp, temp + 4, [](const ImVec2 i, const ImVec2 j) {return (i.x < j.x); });
	std::sort(temp, temp + 2, [](const ImVec2 i, const ImVec2 j) {return (i.y < j.y); });
	std::sort(temp + 2, temp + 4, [](const ImVec2 i, const ImVec2 j) {return (i.y < j.y); });
	top_left = temp[0];
	bottom_right = temp[3];
	//topLeft = start;
	//bottomRight = end;
	top_right = { bottom_right.x,top_left.y };
	bottom_left = { top_left.x ,bottom_right.y };
	calculate_diagonal();
}
item::item() : color{red}, id{0}, collision(false)
{
}

item::item(ImVec2 start, ImVec2 end, const colors_id color):color{color},start{start},end{end},id{0}, collision(false)
{
	//convert();
	calculate();
}

void item::calculate_diagonal()
{
	one = { (bottom_right.y - top_left.y) / (bottom_right.x - top_left.x), bottom_right.y - (bottom_right.y - top_left.y) / (bottom_right.x - top_left.x) * bottom_right.x };
	two = { -(bottom_right.y - top_left.y) / (bottom_right.x - top_left.x), top_left.y + (bottom_right.y - top_left.y) / (bottom_right.x - top_left.x) * bottom_right.x };
}
bool operator==(const item& lhs, const item& rhs)
{
    return lhs.top_left.x == rhs.top_left.x && lhs.top_left.y == rhs.top_left.y && lhs.bottom_right.x == rhs.bottom_right.x && lhs.bottom_right.y == rhs.bottom_right.y;
}
std::ostream& operator<<(std::ostream& os, const item& obj)
{
	return os << obj.top_left.x << '\t' << obj.top_left.y << '\t' << obj.bottom_right.x << '\t' << obj.bottom_right.y << '\t' << obj.color << '\t' << std::abs((obj.bottom_right.x - obj.top_left.x) * (obj.bottom_right.y - obj.top_left.y));
}