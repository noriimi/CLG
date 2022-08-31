#include "myApp.h"
#include "imgui.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "collisionEngine.h"
//int WinMain(int, char**)
std::vector<Item> Items;
int main(int, char**)
{
	Item a11, b11, c11, d11;
	a11 = { {170,80}, {230,480},RED };
	b11 = { {540,80},{610,540},RED };
	c11 = { {120,140},{710,200},RED };
	d11 = { {100,400},{700,450},RED };	
	Items.push_back(a11);
	Items.push_back(b11);
	Items.push_back(c11);
	Items.push_back(d11);	
	myApp app;
	collisionEngine col{ Items };
	col.run();
	auto a = col.getRest();
	auto b = col.getCollisions();
	//app.final =  {a.cbegin(),a.cend()};
	//app.collisions = { b.cbegin(),b.cend() };
	app.Run();
	return 0;
}
