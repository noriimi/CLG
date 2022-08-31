#include "myApp.h"
#include "ColorsID.h"
#include <algorithm>
#include <cmath>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <map>
#include "ItemWrapper.h"
bool doOverlap(ImVec2 l1, ImVec2 r1, ImVec2 l2, ImVec2 r2)
{
	// if rectangle has area 0, no overlap
	if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
		return false;

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y <= l2.y || r2.y <= l1.y)
		return false;

	return true;
}
Item calcOverlap(Item a, Item b)
{
	ImVec2 a1, a2;
	a1 = { std::max(a.topLeft.x, b.topLeft.x), std::max(a.topLeft.y, b.topLeft.y) };
	a2 = { std::min(a.bottomRight.x, b.bottomRight.x),std::min(a.bottomRight.y, b.bottomRight.y) };
	Item c = { a1 , a2,a.color };
	return c;
}
bool doOverlap(Item a, Item b)
{
	/*if (a == b)
		return false;*/
	return doOverlap(a.topLeft, a.bottomRight, b.topLeft, b.bottomRight);
}

void myApp::collide()
{
	vector.clear();
	vector.insert({ 1, {Items.cbegin(),Items.cend()} });
	collisions.clear();
	anomalies.clear();
	auto& r = vector.at(vector.size());
	std::vector<ItemWrapper> vectorix(r.cbegin(), r.cend());
	auto s = vector.size();
	vector.insert({ (int)(s + 1), {} });
	int counter = 0;

	for (auto& it : vectorix)
	{
		for (auto& i : vectorix)
		{
			if (it.item == i.item)
				continue;
			if (doOverlap(it.item, i.item))
			{
				it.collision = true;
				i.collision = true;
				auto h = calcOverlap(it.item, i.item);
				bool b1, b2, b3, b4, b5, b6, b7, b8, b9;
				b1 = h.topLeft.y == i.item.topLeft.y && h.bottomRight.y != i.item.bottomRight.y;
				b2 = h.topLeft.y == it.item.topLeft.y && h.bottomRight.y != it.item.bottomRight.y;
				b3= h.topLeft.x == i.item.topLeft.x && h.bottomRight.x != i.item.bottomRight.x;
				b4= h.topLeft.x == it.item.topLeft.x && h.bottomRight.x != it.item.bottomRight.x;

				b5= h.topLeft.y != i.item.topLeft.y && h.bottomRight.y == i.item.bottomRight.y;
				b6= h.topLeft.y != it.item.topLeft.y && h.bottomRight.y == it.item.bottomRight.y;

				b7= h.topLeft.x != i.item.topLeft.x && h.bottomRight.x == i.item.bottomRight.x;
				b8= h.topLeft.x != it.item.topLeft.x && h.bottomRight.x == it.item.bottomRight.x;
				counter++;
				//
				if (!(b1 || b2 || b3 || b4 || b5 || b6 || b7 || b8))
				{
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
						vector.at(s + 1).insert({ a1 });
					if (a2.area())
						vector.at(s + 1).insert({ a2 });
					if (a3.area())
						vector.at(s + 1).insert({ a3 });
					if (a4.area())
						vector.at(s + 1).insert({ a4 });
					if (b1.area())
						vector.at(s + 1).insert({ b1 });
					if (b2.area())
						vector.at(s + 1).insert({ b2 });
					if (b3.area())
						vector.at(s + 1).insert({ b3 });
					if (b4.area())
						vector.at(s + 1).insert({ b4 });

					ItemWrapper temp = { h };
					temp.col = true;
					temp.parent = 
					temp.parentB = &it;
					collisions.insert(temp);

				}
				else
				{
					ItemWrapper temp = { h };
					temp.col = true;
					collisions.insert(temp);
					anomalies.insert(temp);
				}
			}
		}
	}
	vector.at(s) = std::unordered_set<ItemWrapper>(vectorix.cbegin(), vectorix.cend());
	std::unordered_set<ItemWrapper> in, out;
	//std::cout << "Kolizje" << std::endl;
	for (auto& i : collisions)
	{
		std::cout << i.item << std::endl;
	}
	for (auto& it : collisions)
	{
		for (auto& i : vector.at(2))
		{
			if (doOverlap(it.item, i.item))
			{
				//top
				if (it.item.bottomRight.x == i.item.bottomRight.x && it.item.topLeft.x == i.item.topLeft.x)
				{
					//auto res=calcOverlap(it.item, i.item);
					Item top, bottom;
					top = { {it.item.topLeft.x,it.item.bottomRight.y},i.item.bottomRight ,i.item.color };
					if (top.area()) {

						in.insert({ top });
					}
					bottom = { i.item.topLeft, {it.item.bottomRight.x,it.item.topLeft.y} ,i.item.color };
					if (bottom.area()) {
						in.insert({ bottom });
					}
					Item o;
					o = { i.item.topLeft,i.item.bottomRight,i.item.color };
					out.insert({ o });

				}
				else if (it.item.bottomRight.y == i.item.bottomRight.y && it.item.topLeft.y == i.item.topLeft.y)
				{
					//auto res=calcOverlap(it.item, i.item);
					Item left, right;
					left = { {it.item.bottomRight.x,it.item.topLeft.y},i.item.bottomRight ,i.item.color };
					right = { i.item.topLeft, {it.item.topLeft.x,it.item.bottomRight.y} ,i.item.color };
					if (left.area()) {
						in.insert({ left });
					}
					if (right.area()) {
						in.insert({ right });
					}
					Item o;
					o = { i.item.topLeft,i.item.bottomRight,i.item.color };
					out.insert({ o });
				}
			}
		}
	}
	for (auto& it : out)
	{
		vector.at(2).erase(it);
	}
	vector.at(2).insert(in.cbegin(), in.cend());
	out.clear();
	for (auto& it : anomalies)
	{
		for (auto& i : vector.at(2))
		{
			if (it.item == i.item)
				continue;
			if (doOverlap(it.item, i.item))
			{
				Item o;
				o = { i.item.topLeft,i.item.bottomRight,i.item.color };
				out.insert({ o });
				auto h = calcOverlap(it.item, i.item);
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
					vector.at(2).insert({ a1 });
					//std::cout << "Kolizja: " <<"a1" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a1 << std::endl << std::endl;
				}
				if (a2.area())
				{
					vector.at(2).insert({ a2 });
					//std::cout << "Kolizja: " << "a2" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a2 << std::endl << std::endl;
				}
				if (a3.area())
				{
					vector.at(2).insert({ a3 });
					//std::cout << "Kolizja: " << "a3" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a3 << std::endl << std::endl;
				}
				if (a4.area())
				{
					vector.at(2).insert({ a4 });
					//std::cout << "Kolizja: " << "a4" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << a4 << std::endl << std::endl;
				}
				if (b1.area())
				{
					vector.at(2).insert({ b1 });
					//	std::cout << "Kolizja: " << "b1" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b1 << std::endl << std::endl;
				}
				if (b2.area())
				{
					vector.at(2).insert({ b2 });
					//std::cout << "Kolizja: " << "b2" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b2 << std::endl << std::endl;
				}
				if (b3.area())
				{
					vector.at(2).insert({ b3 });
					//std::cout << "Kolizja: " << "b3" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b3 << std::endl << std::endl;
				}
				if (b4.area())
				{
					vector.at(2).insert({ b4 });
					//	std::cout << "Kolizja: " << "b4" << '\n' << it.item << '\n' << i.item << '\n' << "Result :" << '\n' << b4 << std::endl << std::endl;
				}

				ItemWrapper temp = { h };
				temp.col = true;
				collisions.insert(temp);

			}
		}
	}
	for (auto& it : out)
	{
		vector.at(2).erase(it);
	}
}

ImColor myApp::meanColor(enum ColorsID a, enum ColorsID b)
{
	ImColor aa, bb;
	aa = Colors[a];
	bb = Colors[b];
	auto mean = [](float a, float b) {return (a + b) / 4.0f; };
	return ImColor(mean(aa.Value.x, bb.Value.x), mean(aa.Value.y, bb.Value.y), mean(aa.Value.z, bb.Value.z), mean(aa.Value.w, bb.Value.w));
}

myApp::myApp()
{
	//:wheel{ 0 }, oldwheel{ 0 }, Offset{ 0.0f,0.0f }, Offsetw{ 0.0f,0.0f }, Scale{ 1.0f,1.0f }, StartPan{ 0.0f,0.0f }, ColorID{ RED }, ColRect{ Colors[ColorID] }, show_another_window{ false }, show_demo_window{ true }, ve{ 0,0,0,0 }, ve2{ 0,0 }
}
myApp::myApp(std::map<int, std::unordered_set<ItemWrapper>> v)
{
	vector = v;
}
ImVec2 myApp::WorldToScreen(const ImVec2 World)
{
	return ImVec2((int)((World.x - Offset.x) * Scale.x) - Offsetw.x, (int)((World.y - Offset.y) * Scale.y) - Offsetw.y);
}
ImVec2 myApp::ScreenToWorld(const ImVec2 Screen)
{
	return ImVec2(((float)(Screen.x + Offsetw.x) / Scale.x) + Offset.x, ((float)(Screen.y + Offsetw.y) / Scale.y) + Offset.y);
}
void myApp::initOffset(ImVec2 in)
{
	Offset.x = -in.x;
	Offset.y = -in.y;
	InitOffset = in;
	runned = true;
}

void myApp::Init()
{
	show_demo_window = true;
	show_another_window = false;
	wheel = 0;
	oldwheel = 0;
	Offset = { 0.0f,0.0f };
	Offsetw = { 0.0f,0.0f };
	Scale = { 1.0f,1.0f };
	StartPan = { 0.0f,0.0f };
	vector.insert({ 1,{} });
	/*for (int i = 0; i < 7; i++)
	{
		Colors[i] = (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f);
	}*/
	ColorID = RED;
	ColRect = Colors[ColorID];
	Items.clear();
	for (auto& it : vector.at(1))
		Items.push_back(it.item);
}
void myApp::Update()
{
	static ImVector<ImVec2> points;
	static bool opt_enable_grid = false;
	static bool opt_filled = false;
	static bool adding_line = false;
	static int time = 0;
	io = ImGui::GetIO();
	oldwheel = wheel;
	wheel += (int)io.MouseWheel;
	ImVec2 Mouse = io.MousePos;
	ImGui::Begin("test");
	ImGui::Checkbox("Enable grid", &opt_enable_grid);
	ImGui::Checkbox("Fill", &opt_filled);
	ImGui::Text("Kursor  %f     \t \t  %f", (double)io.MousePos.x - ve2[0], (double)io.MousePos.y - ve2[1]);
	//
	ImGui::InputFloat4("POS", ve);
	for (int i = 0; i < 6; i++)
	{
		if (i > 0)
			ImGui::SameLine();
		ImGui::PushID(i);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)Colors[i]);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Click"))
		{
			ColRect = Colors[i];
			ColorID = ColorsID(i);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
	}
	// Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
	// Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
	// To use a child window instead we could use, e.g:
	// Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
	ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
	ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
	Offsetw.x = -(canvas_p0.x - InitOffset.x);
	Offsetw.y = -(canvas_p0.y - InitOffset.y);
	// Resize canvas to what's available
	if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
	if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
	ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
	const float mouse_threshold_for_pan = opt_filled ? -1.0f : 0.0f;
	if (!runned)
		initOffset(canvas_p0);


	// Draw border and background color

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
	draw_list->PushClipRect(canvas_p0, canvas_p1);
	// This will catch our interactions
	ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_hovered = ImGui::IsItemHovered(); // Hovered
	const bool is_active = ImGui::IsItemActive();   // Held

	if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
	{
		Offset.x -= io.MouseDelta.x / Scale.x;
		Offset.y -= io.MouseDelta.y / Scale.y;
	}
	// Add first and second point
	if (is_hovered && !adding_line && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		item.start = ScreenToWorld(Mouse);
		item.end = ScreenToWorld(Mouse);
		adding_line = true;
	}
	if (adding_line && 0)
	{
		item.end = ScreenToWorld(Mouse);
		item.color = ColorID;
		item.convert();
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			if (item.area())
			{
				item.calculate();
				ItemWrapper ar(&root, item);
				update = true;
				/*ve[0] = item.start.x;
				ve[1] = item.start.y;
				ve[2] = item.end.x;
				ve[3] = item.end.y;*/
				Items.push_back(item);
				vector.at(1).insert(ar);
				item.start = { 0,0 };
				item.end = { 0,0 };
			}
			adding_line = false;
		}
	}
	/*if (opt_enable_grid)
	{
		Offset.x = 0;
		Offset.y = 0;
		wheel = 4;
		oldwheel = 4;
	}*/
	ImVec2 MouseWorld_BeforeZoom = ScreenToWorld(Mouse);
	if (wheel - oldwheel > 0)
	{
		Scale.x *= 1.1f;
		Scale.y *= 1.1f;
	}
	if (wheel - oldwheel < 0)
	{
		Scale.x *= 0.9f;
		Scale.y *= 0.9f;
	}
	ImVec2 MouseWorld_AfterZoom = ScreenToWorld(Mouse);

	Offset.x += (MouseWorld_BeforeZoom.x - MouseWorld_AfterZoom.x);
	Offset.y += (MouseWorld_BeforeZoom.y - MouseWorld_AfterZoom.y);

	float fWorldLeft, fWorldTop, fWorldRight, fWorldBottom;
	fWorldLeft = ScreenToWorld(canvas_p0).x;
	fWorldTop = ScreenToWorld(canvas_p0).y;
	fWorldRight = ScreenToWorld(canvas_p1).x;
	fWorldBottom = ScreenToWorld(canvas_p1).y;

	ImVec2 Start = { 10 * (float)floor(fWorldLeft / 10) ,10 * (float)floor(fWorldTop / 10) };
	ImVec2 End = { 10 * (float)ceil(fWorldRight / 10) ,10 * (float)ceil(fWorldBottom / 10) };
	for (Start.x; Start.x <= End.x; Start.x += 10)
	{
		ImVec2 Pixel_Start = { WorldToScreen(Start).x,WorldToScreen(Start).y }, Pixel_End = { WorldToScreen(End).x,WorldToScreen(End).y };
		draw_list->AddLine(Pixel_Start, ImVec2(Pixel_Start.x, Pixel_End.y), IM_COL32(100, 100, 100, 100));
	}

	Start = { 10 * (float)floor(fWorldLeft / 10) ,10 * (float)floor(fWorldTop / 10) };
	End = { 10 * (float)ceil(fWorldRight / 10) ,10 * (float)ceil(fWorldBottom / 10) };
	for (Start.y; Start.y <= End.y; Start.y += 10)
	{
		ImVec2 Pixel_Start = { WorldToScreen(Start).x,WorldToScreen(Start).y }, Pixel_End = { WorldToScreen(End).x,WorldToScreen(End).y };
		draw_list->AddLine(Pixel_Start, ImVec2(Pixel_End.x, Pixel_Start.y), IM_COL32(100, 100, 100, 100));
	}



	draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(0, 255, 255, 255));
	/*for (auto& it : Items)
	{
		it.calculate();
		draw_list->AddRectFilled(WorldToScreen(it.topLeft), WorldToScreen(it.bottomRight), meanColor(it.color, it.color));
	}*/
	if (opt_filled)
	{
		time = (++time) % 20;
		ve[3] = time;
		opt_filled = false;
	}
	if (opt_enable_grid)
	{
		final.clear();
		draw_list->AddRectFilled(WorldToScreen({ 0 + 50,0 + 50 }), WorldToScreen({ 50 + 50,50 + 50 }), Colors[YELLOW]);
		draw_list->AddRectFilled(WorldToScreen({ 0 + 50,50 + 50 }), WorldToScreen({ 50 + 50,100 + 50 }), Colors[RED]);
		if (update)
		{
			//collide();
			update = false;
		}
		/*for (auto& it : vector)
		{
			for (auto& i : it.second)
			{
				if (!i.collision&&1)
				{
					draw_list->AddRectFilled(WorldToScreen(i.item.topLeft), WorldToScreen(i.item.bottomRight), Colors[i.item.color]);
				}
			}
		}*/
		int uu = 0;
		{
			for (auto& it : vector.at(1))
			{
				draw_list->AddRect(WorldToScreen(it.item.topLeft), WorldToScreen(it.item.bottomRight), Colors[it.item.color]);
			}

		}
		if (vector.size() > 1)
		{
			for (auto& i : vector.at(2))
			{
				if ((time!=0&&uu == time-1) || time==0)
				{
					draw_list->AddRectFilled(WorldToScreen(i.item.topLeft), WorldToScreen(i.item.bottomRight), Colors[i.item.color]);
				}
				uu++;
			}
		}


		for (auto& it : collisions)
		{
			draw_list->AddRectFilled(WorldToScreen(it.item.topLeft), WorldToScreen(it.item.bottomRight), Colors[YELLOW]);
		}
	}
	else
	{
		for (auto& it : vector.at(1))
		{
			draw_list->AddRect(WorldToScreen(it.item.topLeft), WorldToScreen(it.item.bottomRight), Colors[it.item.color]);
		}

	}


	if (item.area())
		draw_list->AddRect(WorldToScreen(item.start), WorldToScreen(item.end), ColRect);


	draw_list->PopClipRect();
	ImGui::End();
}
