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
int main(int, char**)
{
	//myApp app;

	// a.Start();
   // app.Run();
	// a.End();


	Item a11, b11, c11, d11;
	a11 = { {170,80}, {230,540},RED };
	b11 = { {120,140},{710,200},RED };
	c11 = { {530,90},{610,530},RED };
	d11 = { {170,10},{180,100},RED };
	ItemWrapper root;
	ItemWrapper ar(&root, a11);
	ItemWrapper br(&root, b11);
	ItemWrapper cr(&root, c11);
	ItemWrapper dr(&root, d11);
	std::map<int, std::unordered_set<ItemWrapper>> mapa;
	mapa.insert({ 1,{} });
	mapa.at(1).insert(ar);
	mapa.at(1).insert(br);
	mapa.at(1).insert(cr);
	//mapa.at(1).insert(dr);
	std::cout << std::boolalpha << doOverlap(a11, d11) << std::endl;
	bool condition = true;
	while (condition)
	{
		auto& r = mapa.at(mapa.size());
		std::vector<ItemWrapper> vectorix(r.cbegin(), r.cend());
		auto s = mapa.size();
		std::cout << "Level :" << s << std::endl << std::endl;
		mapa.insert({ (int)(s + 1), {} });
		int counter = 0;

		for (auto& it : vectorix)
		{
			for (auto& i : vectorix)
			{
				if (it.item == i.item)
					continue;
				if (doOverlap(it.item, i.item))
				{
					auto h = calcOverlap(it.item, i.item);

					it.collision = true;
					i.collision = true;
					counter++;
					ImVec2 a, b, c, d;
					a = h.topLeft;
					c = h.bottomRight;
					b = { c.x,a.y };
					d = { a.x,c.y };
					Item a1, a2, a3, a4, b1, b2, b3, b4;
					a1 = { it.item.topLeft,{it.item.bottomRight.x,b.y},it.item.color };

					a2 = { {it.item.topLeft.x,d.y }, it.item.bottomRight, it.item.color };

					a3 = { {it.item.topLeft.x,a.y}, d,it.item.color };

					a4 = { b,{it.item.bottomRight.x,c.y},it.item.color };

					b1 = { i.item.topLeft,{i.item.bottomRight.x,b.y},i.item.color };
					b2 = { {i.item.topLeft.x,d.y}, i.item.bottomRight,i.item.color };
					b3 = { {i.item.topLeft.x,a.y}, d,i.item.color };
					b4 = { b,{i.item.bottomRight.x,c.y},i.item.color };
					if (a1.area())
					{
						mapa.at(s + 1).insert({ a1 });
						//std::cout << "Kolizja: " <<"a1" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a1 << std::endl << std::endl;
					}
					if (a2.area())
					{
						mapa.at(s + 1).insert({ a2 });
						//std::cout << "Kolizja: " << "a2" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a2 << std::endl << std::endl;
					}
					if (a3.area())
					{
						mapa.at(s + 1).insert({ a3 });
						//std::cout << "Kolizja: " << "a3" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a3 << std::endl << std::endl;
					}
					if (a4.area())
					{
						mapa.at(s + 1).insert({ a4 });
						//std::cout << "Kolizja: " << "a4" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a4 << std::endl << std::endl;
					}
					if (b1.area())
					{
						mapa.at(s + 1).insert({ b1 });
						//	std::cout << "Kolizja: " << "b1" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b1 << std::endl << std::endl;
					}
					if (b2.area())
					{
						mapa.at(s + 1).insert({ b2 });
						//std::cout << "Kolizja: " << "b2" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b2 << std::endl << std::endl;
					}
					if (b3.area())
					{
						mapa.at(s + 1).insert({ b3 });
						//std::cout << "Kolizja: " << "b3" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b3 << std::endl << std::endl;
					}
					if (b4.area())
					{
						mapa.at(s + 1).insert({ b4 });
						//	std::cout << "Kolizja: " << "b4" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b4 << std::endl << std::endl;
					}
					bool ba = !(h == it.item || h == i.item);
					bool bb = (it.item.topLeft.x == h.topLeft.x) && (it.item.topLeft.y == h.topLeft.y);
					bool bc = (it.item.bottomRight.x == h.bottomRight.x) && (it.item.bottomRight.y == h.bottomRight.y);
					bool bd = (i.item.topLeft.x == h.topLeft.x) && (i.item.topLeft.y == h.topLeft.y);
					bool be = (i.item.bottomRight.x == h.bottomRight.x) && (i.item.bottomRight.y == h.bottomRight.y);
					if (ba && !(bc && bd || bb && be))
					{
						ItemWrapper temp = { h };
						temp.col = true;
						mapa.at(s + 1).insert(temp);
						std::cout << "Kolizja: " << "h" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << h << std::endl << std::endl << std::endl;
					}
				}
			}
		}
		mapa.at(s) = std::unordered_set<ItemWrapper>(vectorix.cbegin(), vectorix.cend());
		if (mapa.at(mapa.size()).empty())
		{
			condition = false;
			std::cout << "Wykryto wszystkie kolizje" << std::endl;
		}

	}


	std::cout << std::endl << std::endl;
	for (auto& it : mapa)
	{
		for (auto& i : it.second)
		{
			if (!i.collision && i.col)
			{

				std::cout << i.item << std::endl;
			}
		}

	}
	std::cout << std::endl << std::endl;


	int count = 0;
	std::cout << std::boolalpha;
	for (auto& it : mapa)
	{
		for (auto& i : it.second)
		{
			if (!i.collision)
			{
				std::cout << i.item << '\t' << i.col << std::endl;
				count++;
			}
		}
	}
	std::cout << count << std::endl;


	myApp app;
	//	app.vector = mapa;
		// a.Start();
	app.Run();
	// a.End();

	return 0;
}
