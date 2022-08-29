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
	bool condition = true;
	auto copy = vector.at(1);
	vector.clear();
	vector.insert({ 1, {} });
	vector.at(1) = copy;
	while (condition)
	{
		auto& r = vector.at(vector.size());
		std::vector<ItemWrapper> vectorix(r.cbegin(), r.cend());
		auto s = vector.size();
		vector.insert({ (int)(s + 1), {} });
		int counter = 0;

		for (auto& it : vectorix)
		{
			for (auto& i : vectorix)
			{
				if (it == i)
					continue;
				if (doOverlap(it.item, i.item))
				{
					it.collision = true;
					i.collision = true;
					auto h = calcOverlap(it.item, i.item);
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


					bool ba = !(h == it.item || h == i.item);
					bool bb = (it.item.topLeft.x == h.topLeft.x) && (it.item.topLeft.y == h.topLeft.y);
					bool bc = (it.item.bottomRight.x == h.bottomRight.x) && (it.item.bottomRight.y == h.bottomRight.y);
					bool bd = (i.item.topLeft.x == h.topLeft.x) && (i.item.topLeft.y == h.topLeft.y);
					bool be = (i.item.bottomRight.x == h.bottomRight.x) && (i.item.bottomRight.y == h.bottomRight.y);
					if (ba && !(bc && bd || bb && be))
					{
						ItemWrapper temp = { h };
						temp.col = true;
						vector.at(s + 1).insert(temp);
					}
				}
			}
		}
		vector.at(s) = std::unordered_set<ItemWrapper>(vectorix.cbegin(), vectorix.cend());
		if (vector.at(vector.size()).empty())
		{
			condition = false;
			//std::cout << "Wykryto wszystkie kolizje" << std::endl;
		}

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
}
void myApp::Update()
{
	static ImVector<ImVec2> points;
	static bool opt_enable_grid = false;
	static bool opt_filled = false;
	static bool adding_line = false;

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
	if (adding_line)
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
				ve[0] = item.start.x;
				ve[1] = item.start.y;
				ve[2] = item.end.x;
				ve[3] = item.end.y;
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

	if (opt_enable_grid)
	{
		final.clear();

		if (update)
		{
			collide();
			update = false;
		}
		for (auto& it : vector)
		{
			for (auto& i : it.second)
			{
				if (!i.collision && !i.col)
				{
					final.push_back(i);
				draw_list->AddRect(WorldToScreen(i.item.topLeft), WorldToScreen(i.item.bottomRight), Colors[i.item.color]);
				}
				else if (i.col)
				{
					draw_list->AddRectFilled(WorldToScreen(i.item.topLeft), WorldToScreen(i.item.bottomRight), Colors[GREEN]);
					final.push_back(i);
				}
			}
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
