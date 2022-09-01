#pragma once
#include "BaseApp.h"
#include "imgui.h"
#include <vector>
#include "Item.h"


class my_app final : public base_app
{
public:
    bool show_demo_window{};
    bool show_another_window{};
    int wheel{};
    int oldwheel{};
    bool updated{};
    std::vector < item> collisions;
    ImVec2 offset;
    ImVec2 offsetw;
    ImVec2 scale;
    ImVec2 start_pan;
    ImVec2 first_offset;
    float ve[4]{};
    float ve2[2]{};
    ImColor colors[6] = { ImColor(255,0,0,127),ImColor(255,255,0,127),ImColor(0,255,0,255),ImColor(0,0,255,255),ImColor(128,0,128,255),ImColor(255,28,121,255) };
    ImColor col_rect;
    colors_id color_id;
    std::vector<item> Items;
    bool runned = false;
    bool click = false;
    item curr_item;
    [[nodiscard]] ImColor mean_color(colors_id a, colors_id b) const;
    my_app();
    explicit my_app(const std::vector<item>& v);
    void init() override;
    void update() override;
    void init_offset(ImVec2);
    [[nodiscard]] ImVec2 world_to_screen(ImVec2 world) const;
    [[nodiscard]] ImVec2 screen_to_world(ImVec2 screen) const;
    
};

