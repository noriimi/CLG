#pragma once
#include "BaseApp.h"
#include "imgui.h"
#include <vector>
#include "Item.h"
#include "ItemWrapper.h"


class myApp: public BaseApp
{
public:
    bool show_demo_window;
    bool show_another_window;
    int wheel;
    int oldwheel;
    bool update;
    std::vector < ItemWrapper> final,collisions;
    ImVec2 Offset;
    ImVec2 Offsetw;
    ImVec2 Scale;
    ImVec2 StartPan;
    ImVec2 InitOffset;
   // enum ColorsID { RED, YELLOW, GREEN, BLUE, PURPLE, PINK };
    float ve[4];
    float ve2[2];
    ImColor Colors[6] = { ImColor(255,0,0,127),ImColor(255,255,0,127),ImColor(0,255,0,255),ImColor(0,0,255,255),ImColor(128,0,128,255),ImColor(255,28,121,255) };
    ImColor ColRect;
    ColorsID ColorID;
    void collide();
    ItemWrapper root;
    std::vector<Item> Items;
    std::vector<Item> TransformedItems;
    std::vector<Item> CollisionItems;
    bool runned = false;
    bool click = false;
    Item item;
    Item curItem;
    ImColor meanColor(enum ColorsID a, enum ColorsID b);
    myApp();
    myApp(std::vector<ItemWrapper> v);
    void Init() override;
    void Update() override;
    void initOffset(ImVec2);
    void transform();
    void remove(std::vector<Item>& v);
    float diagonal(ImVec2 a_,ImVec2 b_);
    ImVec2 WorldToScreen(const ImVec2 World);
    ImVec2 ScreenToWorld(const ImVec2 Screen);
    
};

