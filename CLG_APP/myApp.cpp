#include "myApp.h"
#include <algorithm>
#include <cmath>
ImColor myApp::meanColor(enum ColorsID a, enum ColorsID b)
{
	ImColor aa, bb;
	aa = Colors[a];
	bb = Colors[b];
	auto mean = [](float a, float b) {return (a + b) / 8.0f; };
	return ImColor(mean(aa.Value.x, bb.Value.x), mean(aa.Value.y, bb.Value.y), mean(aa.Value.z, bb.Value.z),mean(aa.Value.w, bb.Value.w));
}

myApp::myApp() :wheel{ 0 }, oldwheel{ 0 }, Offset{ 0.0f,0.0f }, Offsetw{ 0.0f,0.0f }, Scale{ 1.0f,1.0f }, StartPan{ 0.0f,0.0f }, ColorID{ RED }, ColRect{ Colors[ColorID]},show_another_window{false},show_demo_window{true},ve{0,0,0,0},ve2{0,0}
{
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
	/* one = { (end.y - start.y) / (end.x - start.x), end.y - (end.y - start.y) / (end.x - start.x) * end.x };
	 two = { -(end.y - start.y) / (end.x - start.x), start.y + (end.y - start.y) / (end.x - start.x) * end.x };*/
	a = start;
	c = end;
	b = { end.x,start.y };
	d = { start.x,end.y };
	ImVec2 temp[4] = { a, b, c, d };
	std::sort(temp, temp + 4, [](ImVec2 i, ImVec2 j) {return (i.x < j.x); });
	std::sort(temp, temp + 2, [](ImVec2 i, ImVec2 j) {return (i.y < j.y); });
	std::sort(temp + 2, temp + 4, [](ImVec2 i, ImVec2 j) {return (i.y < j.y); });
	topLeft = temp[0];
	bottomRight = temp[3];
	one = { (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x), bottomRight.y - (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x) * bottomRight.x };
	two = { -(bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x), topLeft.y + (bottomRight.y - topLeft.y) / (bottomRight.x - topLeft.x) * bottomRight.x };

}
Item::Item() :id{ -1 }, color{RED} {

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
				Items.push_back(item);
				item.start = { 0,0 };
				item.end = { 0,0 };
			}
			adding_line = false;
		}
	}
	ve[0] = item.start.x;
	ve[1] = item.start.y;
	ve[2] = item.end.x;
	ve[3] = item.end.y;
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
	if (!opt_filled)
	{
		for (auto& it : Items)
		{
			it.calculate();
			draw_list->AddRect(WorldToScreen(it.start), WorldToScreen(it.end), Colors[it.color]);
			draw_list->AddLine(WorldToScreen(ImVec2(it.start.x, it.start.x * it.one.x + it.one.y)), WorldToScreen(ImVec2(it.end.x, it.end.x * it.one.x + it.one.y)), ImColor(128, 255, 255, 255));
			draw_list->AddLine(WorldToScreen(ImVec2(it.start.x, it.start.x * it.two.x + it.two.y)), WorldToScreen(ImVec2(it.end.x, it.end.x * it.two.x + it.two.y)), ImColor(255, 128, 255, 255));
			//draw_list->AddCircle(WorldToScreen(it.topLeft), 5 * Scale.x, ImColor(0, 255, 0, 192));
			//draw_list->AddCircle(WorldToScreen(it.bottomRight), 5 * Scale.x, ImColor(255, 0, 255, 192));
			//auto& i = Items.back();
			for (auto& i : Items)
			{
				it.calculate();
				if (it.topLeft.x != i.topLeft.x && it.topLeft.y != i.topLeft.y && it.bottomRight.x != i.bottomRight.x && it.bottomRight.y != i.bottomRight.y)
				{
					ImVec2 a, b, c, d;
					bool q, w, e, r;
					if(it.one.x-i.one.x!=0)
					a = ImVec2((i.one.y - it.one.y) / (it.one.x - i.one.x), (i.one.y - it.one.y) / (it.one.x - i.one.x) * it.one.x + it.one.y);
					if (it.one.x - i.two.x != 0)
					b = ImVec2((i.two.y - it.one.y) / (it.one.x - i.two.x), (i.two.y - it.one.y) / (it.one.x - i.two.x) * it.one.x + it.one.y);
					if (it.two.x - i.one.x != 0)
					c = ImVec2((i.one.y - it.two.y) / (it.two.x - i.one.x), (i.one.y - it.two.y) / (it.two.x - i.one.x) * it.two.x + it.two.y);
					if (it.two.x - i.two.x != 0)
					d = ImVec2((i.two.y - it.two.y) / (it.two.x - i.two.x), (i.two.y - it.two.y) / (it.two.x - i.two.x) * it.two.x + it.two.y);
					q = ((it.topLeft.x <= a.x && a.x <= it.bottomRight.x) && (it.topLeft.y <= a.y && a.y <= it.bottomRight.y)) || ((i.topLeft.x <= a.x && a.x <= i.bottomRight.x) && (i.topLeft.y <= a.y && a.y <= i.bottomRight.y));
					w = (it.topLeft.x <= b.x && b.x <= it.bottomRight.x && it.topLeft.y <= b.y && b.y <= it.bottomRight.y) || (i.topLeft.x <= b.x && b.x <= i.bottomRight.x && i.topLeft.y <= b.y && b.y <= i.bottomRight.y);
					e = (it.topLeft.x <= c.x && c.x <= it.bottomRight.x && it.topLeft.y <= c.y && c.y <= it.bottomRight.y) || (i.topLeft.x <= c.x && c.x <= i.bottomRight.x && i.topLeft.y <= c.y && c.y <= i.bottomRight.y);
					r = (it.topLeft.x <= d.x && d.x <= it.bottomRight.x && it.topLeft.y <= d.y && d.y <= it.bottomRight.y) || (i.topLeft.x <= d.x && d.x <= i.bottomRight.x && i.topLeft.y <= d.y && d.y <= i.bottomRight.y);
					if (q)
						draw_list->AddCircleFilled(WorldToScreen(a), 8 * Scale.x, ImColor(128, 0, 128, 200));
					if (w)
						draw_list->AddCircleFilled(WorldToScreen(b), 8 * Scale.x, ImColor(128, 128, 0, 200));
					if (e)
						draw_list->AddCircleFilled(WorldToScreen(c), 8 * Scale.x, ImColor(0, 128, 128, 200));
					if (r)
						draw_list->AddCircleFilled(WorldToScreen(d), 8 * Scale.x, ImColor(128, 255, 128, 200));

					if ((int)q + (int)w + (int)e + (int)r > 3)
						draw_list->AddRectFilled(WorldToScreen(ImVec2(std::max(it.topLeft.x, i.topLeft.x), std::max(it.topLeft.y, i.topLeft.y))), WorldToScreen(ImVec2(std::min(it.bottomRight.x, i.bottomRight.x), std::min(it.bottomRight.y, i.bottomRight.y))), meanColor(it.color,i.color));



				}
			}
		}
		if (item.area())
			draw_list->AddRect(WorldToScreen(item.start), WorldToScreen(item.end), ColRect);
	}
	else
	{
		for (auto& it : Items)
		{
			draw_list->AddRectFilled(WorldToScreen(it.start), WorldToScreen(it.end), Colors[it.color]);
		}
		if (item.area())
			draw_list->AddRectFilled(WorldToScreen(item.start), WorldToScreen(item.end), ColRect);
	}
	draw_list->PopClipRect();
	ImGui::End();
}
