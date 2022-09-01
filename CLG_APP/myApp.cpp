#include "myApp.h"
#include "ColorsID.h"
#include <cmath>
#include "collisionEngine.h"

ImColor my_app::mean_color(const colors_id a, const colors_id b) const
{
	const ImColor aa = colors[a];
	const ImColor bb = colors[b];
	auto mean = [](const float lhs_a, const float rhs_b) {
		return (lhs_a + rhs_b) / 4.0f;
	};
	return {mean(aa.Value.x, bb.Value.x), mean(aa.Value.y, bb.Value.y), mean(aa.Value.z, bb.Value.z), mean(aa.Value.w, bb.Value.w)
	};
}

my_app::my_app():
	color_id()
{
	//:wheel{ 0 }, oldwheel{ 0 }, Offset{ 0.0f,0.0f }, Offsetw{ 0.0f,0.0f }, Scale{ 1.0f,1.0f }, StartPan{ 0.0f,0.0f }, ColorID{ RED }, ColRect{ Colors[ColorID] }, show_another_window{ false }, show_demo_window{ true }, ve{ 0,0,0,0 }, ve2{ 0,0 }
}

my_app::my_app(const std::vector < item >& v): color_id()
{
	Items = v;
}

ImVec2 my_app::world_to_screen(const ImVec2 world) const
{
	return {
		static_cast<int>((world.x - offset.x) * scale.x) - offsetw.x,
		static_cast<int>((world.y - offset.y) * scale.y) - offsetw.y
	};
}
ImVec2 my_app::screen_to_world(const ImVec2 screen) const
{
	return {((screen.x + offsetw.x) / scale.x) + offset.x, ((screen.y + offsetw.y) / scale.y) + offset.y};
}
void my_app::init_offset(const ImVec2 in) {
	offset.x = -in.x;
	offset.y = -in.y;
	first_offset = in;
	runned = true;
}

void my_app::init() {
	show_demo_window = true;
	show_another_window = false;
	wheel = 0;
	oldwheel = 0;
	offset = {
	  0.0f,
	  0.0f
	};
	offsetw = {
	  0.0f,
	  0.0f
	};
	scale = {
	  1.0f,
	  1.0f
	};
	start_pan = {
	  0.0f,
	  0.0f
	};
	color_id = red;
	col_rect = colors[color_id];
	//Items.clear();
}
void my_app::update() {
	static ImVector < ImVec2 > points;
	static bool opt_enable_grid = false;
	static bool opt_filled = false;
	static bool adding_line = false;
	static int time = 0;
	io = ImGui::GetIO();
	oldwheel = wheel;
	wheel += static_cast<int>(io.MouseWheel);
	ImVec2 mouse = io.MousePos;
	ImGui::Begin("test");
	ImGui::Checkbox("Enable grid", &opt_enable_grid);
	ImGui::Checkbox("Fill", &opt_filled);
	ImGui::Text("Kursor  %f     \t \t  %f", static_cast<double>(io.MousePos.x) - ve2[0],
	            static_cast<double>(io.MousePos.y) - ve2[1]);
	//
	ImGui::InputFloat4("POS", ve);
	for (int i = 0; i < 6; i++) {
		if (i > 0)
			ImGui::SameLine();
		ImGui::PushID(i);
		ImGui::PushStyleColor(ImGuiCol_Button, static_cast<ImVec4>(colors[i]));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, static_cast<ImVec4>(ImColor::HSV(i / 7.0f, 0.7f, 0.7f)));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, static_cast<ImVec4>(ImColor::HSV(i / 7.0f, 0.8f, 0.8f)));
		if (ImGui::Button("Click")) {
			col_rect = colors[i];
			color_id = static_cast<colors_id>(i);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
	}
	// Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
	// Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
	// To use a child window instead we could use, e.g:
	// Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
	ImVec2 canvas_p0 = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
	ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
	offsetw.x = -(canvas_p0.x - first_offset.x);
	offsetw.y = -(canvas_p0.y - first_offset.y);
	// Resize canvas to what's available
	if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
	if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
	auto canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
	const float mouse_threshold_for_pan = opt_filled ? -1.0f : 0.0f;
	if (!runned)
		init_offset(canvas_p0);

	// Draw border and background color

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
	draw_list->PushClipRect(canvas_p0, canvas_p1);
	// This will catch our interactions
	ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_hovered = ImGui::IsItemHovered(); // Hovered
	const bool is_active = ImGui::IsItemActive(); // Held

	if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan)) {
		offset.x -= io.MouseDelta.x / scale.x;
		offset.y -= io.MouseDelta.y / scale.y;
	}
	// Add first and second point
	if (is_hovered && !adding_line && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		curr_item.start = screen_to_world(mouse);
		curr_item.end = screen_to_world(mouse);
		adding_line = true;
	}
	if (adding_line) {
		curr_item.end = screen_to_world(mouse);
		curr_item.color = color_id;
		curr_item.convert();
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
			if (curr_item.area()) {
				curr_item.calculate();
				updated = true;
				Items.push_back(curr_item);
				curr_item.start = {
				  0,
				  0
				};
				curr_item.end = {
				  0,
				  0
				};
			}
			adding_line = false;
		}
	}
	ImVec2 mouse_world_before_zoom = screen_to_world(mouse);
	if (wheel - oldwheel > 0) {
		scale.x *= 1.1f;
		scale.y *= 1.1f;
	}
	if (wheel - oldwheel < 0) {
		scale.x *= 0.9f;
		scale.y *= 0.9f;
	}
	ImVec2 mouse_world_after_zoom = screen_to_world(mouse);

	offset.x += (mouse_world_before_zoom.x - mouse_world_after_zoom.x);
	offset.y += (mouse_world_before_zoom.y - mouse_world_after_zoom.y);

	float f_world_left, f_world_top, f_world_right, f_world_bottom;
	f_world_left = screen_to_world(canvas_p0).x;
	f_world_top = screen_to_world(canvas_p0).y;
	f_world_right = screen_to_world(canvas_p1).x;
	f_world_bottom = screen_to_world(canvas_p1).y;

	ImVec2 start = {
	  10 * floor(f_world_left / 10),
	  10 * floor(f_world_top / 10)
	};
	ImVec2 end = {
	  10 * ceil(f_world_right / 10),
	  10 * ceil(f_world_bottom / 10)
	};
	for (start.x; start.x <= end.x; start.x += 10)
	{
		ImVec2 pixel_start = {
		  world_to_screen(start).x,
		  world_to_screen(start).y
		}, pixel_end = {
		  world_to_screen(end).x,
		  world_to_screen(end).y
		};
		draw_list->AddLine(pixel_start, ImVec2(pixel_start.x, pixel_end.y), IM_COL32(100, 100, 100, 100));
	}

	start = {
	  10 * floor(f_world_left / 10),
	  10 * floor(f_world_top / 10)
	};
	end = {
	  10 * ceil(f_world_right / 10),
	  10 * ceil(f_world_bottom / 10)
	};
	for (start.y; start.y <= end.y; start.y += 10) {
		ImVec2 pixel_start = {
		  world_to_screen(start).x,
		  world_to_screen(start).y
		}, pixel_end = {
		  world_to_screen(end).x,
		  world_to_screen(end).y
		};
		draw_list->AddLine(pixel_start, ImVec2(pixel_end.x, pixel_start.y), IM_COL32(100, 100, 100, 100));
	}

	draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(0, 255, 255, 255));
	if (opt_enable_grid) {
		collision_engine col{
		  Items
		};
		col.run();
		auto a = col.get_rest();
		auto b = col.get_collisions();
		for (auto& i : a) {

			draw_list->AddRectFilled(world_to_screen(i.top_left), world_to_screen(i.bottom_right), colors[i.color]);

		}

		for (auto& it : b) {
			draw_list->AddRectFilled(world_to_screen(it.top_left), world_to_screen(it.bottom_right), colors[yellow]);
		}
	}
	else {
		for (auto& it : Items) {
			draw_list->AddRect(world_to_screen(it.top_left), world_to_screen(it.bottom_right), colors[it.color]);
		}

	}

	if (curr_item.area())
		draw_list->AddRect(world_to_screen(curr_item.start), world_to_screen(curr_item.end), col_rect);

	draw_list->PopClipRect();
	ImGui::End();
}