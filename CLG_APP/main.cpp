#include "myApp.h"
#include "imgui.h"
#include "collisionEngine.h"

//int WinMain(int, char**)
std::vector<item> items;
int main(int, char**)
{
	item a11, b11, c11, d11, e11, f11;
	a11 = { {200,600}, {300,700},red };
	b11 = { {200,500}, {400,800},red };
	c11 = { {200,400}, {500,900},red };
	d11 = { {200,300}, {600,1000},red };
	//e11 = { {200,200}, {700,1100},red };
	//f11 = { {200,100}, {800,1200}, red };
	items.push_back(a11);
	items.push_back(b11);
	items.push_back(c11);
	items.push_back(d11);
	//items.push_back(e11);
	//items.push_back(f11);
	//collision_engine col{ items };
	//col.run();
	//col.do_stuff();
	//col.do_stuff();
	//auto a = col.get_rest();
	//auto b = col.get_collisions();
	/*for (auto& it : a)
	{
		std::cout << it << '\t' << it.id << std::endl;
	}
	std::cout << std::endl;
	col.do_stuff();
	a = col.get_rest();
	b = col.get_collisions();
	for (auto& it : a)
	{
		std::cout << it << '\t' << it.id << std::endl;
	}
	std::cout << std::endl;
	col.do_stuff();
	a = col.get_rest();
	b = col.get_collisions();
	for (auto& it : a)
	{
		std::cout << it << '\t' << it.id << std::endl;
	}*/
		
	//collision_engine col;
	my_app app;
	//app.Items = b;
	//app.collisions = b;
	app.run();
	return 0;
}
