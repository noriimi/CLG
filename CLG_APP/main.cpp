#include "myApp.h"
#include "imgui.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <map>
//#include <unordered_set>
#include<set>
//int WinMain(int, char**)
int doStuff();
int id = 0;
std::vector<ItemWrapper> Items, copy;
std::vector<ItemWrapper> in, out, out2;
std::vector<int> outi;
std::vector<ItemWrapper> ResItems;
std::vector<ItemWrapper> collisions;
std::unordered_set<ItemWrapper> input, output;

bool donot(ItemWrapper i, ItemWrapper it)
{
	auto h = calcOverlap(it.item, i.item);
	bool b1, b2, b3, b4, b5, b6, b7, b8, b9;
	b1 = i.item.topLeft.y < it.item.bottomRight.y&& i.item.topLeft.y > it.item.topLeft.y;
	b2 = it.item.topLeft.y < i.item.bottomRight.y&& it.item.topLeft.y > i.item.topLeft.y;
	b3 = it.item.topLeft.y < i.item.bottomRight.y&& it.item.bottomRight.y > i.item.bottomRight.y;
	b4 = i.item.topLeft.y < it.item.bottomRight.y&& i.item.bottomRight.y > it.item.bottomRight.y;
	b5 = i.item.topLeft.x > it.item.topLeft.x && i.item.topLeft.x < it.item.bottomRight.x;
	b6 = it.item.topLeft.x > i.item.topLeft.x && it.item.topLeft.x < i.item.bottomRight.x;
	b7 = i.item.bottomRight.x > it.item.topLeft.x && i.item.bottomRight.x < it.item.bottomRight.x;
	b8 = it.item.bottomRight.x > i.item.topLeft.x && it.item.bottomRight.x < i.item.bottomRight.x;
	b9 = ((b1 || b2) || (b3 || b4)) && ((b5 || b6) || (b7 || b8));
	return !b9;
}

int main(int, char**)
{
	//myApp app;

	// a.Start();
   // app.Run();
	// a.End();

	Item a11, b11, c11, d11;
	a11 = { {170,80}, {230,480},RED };
	b11 = { {540,80},{610,540},RED };
	c11 = { {120,140},{710,200},RED };
	d11 = { {100,400},{700,450},RED };
	a11.id = ++id;
	b11.id = ++id;
	c11.id = ++id;
	d11.id = ++id;


	std::vector<ItemWrapper> anomalies;
	ItemWrapper root;
	ItemWrapper ar(&root, a11);
	ItemWrapper br(&root, b11);
	ItemWrapper cr(&root, c11);
	ItemWrapper dr(&root, d11);
	//std::map<int, std::unordered_set<ItemWrapper>> mapa;
	//mapa.insert({ 1,{} });
	Items.push_back(ar);
	Items.push_back(br);
	Items.push_back(cr);
	Items.push_back(dr);
	ResItems.push_back(ar);
	ResItems.push_back(br);
	ResItems.push_back(cr);
	ResItems.push_back(dr);
	copy = Items;
	input.insert({ ar });
	input.insert({ cr });
	input.insert({ br });
	input.insert({ dr });
	output = { input.begin(), input.end() };
	//while (Items.size())
	//{
	while (true)
	{
		auto a = doStuff();
		std::cout << a << std::endl;
		if (a == 0)
			break;

	}
	for (auto& i : copy)
		std::erase(ResItems, i);
	myApp app;
	app.vector = { {1,{output.cbegin(),output.cend()}}, {2,{output.cbegin(),output.cend()}} };
	//{ {1,} };
	app.collisions = { collisions.cbegin(),collisions.cend() };
	// a.Start();
	app.Run();
	// a.End();

	return 0;
}
int doStuff()
{
	out.clear();
	in.clear();
	bool flag = false;
	bool overlap = false;
	if (!overlap)
	{
		for (auto& i : input)
		{
			if (!overlap)
			{
				auto& a_2 = i;
				for (auto& j : output)
				{
					if (overlap)
						break;
					auto& b_2 = j;
					if (a_2.item == b_2.item)
						continue;
					if (doOverlap(a_2.item, b_2.item))
					{
						overlap = true;
						auto h = calcOverlap(a_2.item, b_2.item);
						if (h.area())
						{
							ImVec2 a, b, c, d;
							flag = false;
							a = h.topLeft;
							c = h.bottomRight;
							b = { c.x,a.y };
							d = { a.x,c.y };
							Item a1, a2, a3, a4, b1, b2, b3, b4;
							a1 = { a_2.item.topLeft,{a_2.item.bottomRight.x,b.y},a_2.item.color };
							a2 = { {a_2.item.topLeft.x,d.y }, a_2.item.bottomRight, a_2.item.color };
							a3 = { {a_2.item.topLeft.x,a.y}, d,a_2.item.color };
							a4 = { b,{a_2.item.bottomRight.x,c.y},a_2.item.color };
							b1 = { b_2.item.topLeft,{b_2.item.bottomRight.x,b.y},b_2.item.color };
							b2 = { {b_2.item.topLeft.x,d.y}, b_2.item.bottomRight,b_2.item.color };
							b3 = { {b_2.item.topLeft.x,a.y}, d,b_2.item.color };
							b4 = { b,{b_2.item.bottomRight.x,c.y},b_2.item.color };

							ItemWrapper temp;
							if (a1.area())
							{
								flag = true;
								a1.id = ++id;
								temp = { {a1} };
								temp.pA = { a_2.item };
								temp.pB = { b_2.item };
								in.push_back({ temp });
							}
							if (a2.area())
							{
								flag = true;
								a2.id = ++id;
								temp = { {a2} };
								temp.pA = { a_2.item };
								temp.pB = { b_2.item };
								in.push_back({ temp });

							}
							if (a3.area())
							{
								flag = true;
								a3.id = ++id;
								temp = { {a3} };
								temp.pA = { a_2.item };
								temp.pB = { b_2.item };
								in.push_back({ temp });
							}
							if (a4.area())
							{

								flag = true;
								a4.id = ++id;
								temp = { {a4} };
								temp.pA = { a_2.item };
								temp.pB = { b_2.item };
								in.push_back({ temp });
							}
							if (b1.area())
							{

								flag = true;
								b1.id = ++id;
								temp = { {b1} };
								temp.pA = { b_2.item };
								temp.pB = { a_2.item };
								in.push_back({ temp });
							}
							if (b2.area())
							{
								flag = true;
								b2.id = ++id;
								temp = { {b2} };
								temp.pA = { b_2.item };
								temp.pB = { a_2.item };
								in.push_back({ temp });

							}
							if (b3.area())
							{
								flag = true;
								b3.id = ++id;
								temp = { {b3} };
								temp.pA = { b_2.item };
								temp.pB = { a_2.item };
								in.push_back({ temp });

							}
							if (b4.area())
							{
								flag = true;
								b4.id = ++id;
								temp = { {b4} };
								temp.pA = { b_2.item };
								temp.pB = { a_2.item };
								in.push_back({ temp });
							}

							collisions.push_back({ h });
							if (flag)
							{
								out.push_back(a_2);
								outi.push_back(a_2.item.id);
								out.push_back(b_2);
								outi.push_back(b_2.item.id);
							}
						}
					}
				}
			}
		}
	}
	for (auto& i : out)
	{
		input.erase(i);
	}
	for (auto& i : in)
	{
		input.insert(i);
	}
	output = { input.cbegin(),input.cend() };
	if (flag && overlap)
		return 1;
	return 0;
}