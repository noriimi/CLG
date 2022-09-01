#include "myApp.h"
#include "imgui.h"
#include "collisionEngine.h"
//int WinMain(int, char**)
std::vector<item> items;
int main(int, char**)
{
	item a11, b11, c11, d11;
	a11 = { {170,80}, {230,480},red };
	b11 = { {540,80},{610,540},red };
	c11 = { {120,140},{710,200},red };
	d11 = { {100,400},{700,450},red };	
	items.push_back(a11);
	items.push_back(b11);
	items.push_back(c11);
	items.push_back(d11);	
	my_app app;
	collision_engine col{ items };
	col.run();
	auto a = col.get_rest();
	auto b = col.get_collisions();
	app.run();
	return 0;
}
