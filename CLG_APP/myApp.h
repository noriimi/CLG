#pragma once
#include "BaseApp.h"
#include "imgui.h"
#include <vector>

enum ColorsID { RED, YELLOW, GREEN, BLUE, PURPLE, PINK };
struct Item
{
public:
    enum ColorsID color;
    ImVec2 start, end;
    ImVec2 one, two;
    ImVec2 topLeft, bottomRight;
    int id;
    void convert();
    float area();
    void calculate();
    Item();
private:
    
    ImVec2 a, b, c, d;
};


class myApp: public BaseApp
{
public:
    bool show_demo_window;
    bool show_another_window;
    int wheel;
    int oldwheel;
    ImVec2 Offset;
    ImVec2 Offsetw;
    ImVec2 Scale;
    ImVec2 StartPan;
    ImVec2 InitOffset;
   // enum ColorsID { RED, YELLOW, GREEN, BLUE, PURPLE, PINK };
    float ve[4];
    float ve2[2];
    ImColor Colors[6] = { ImColor(255,0,0,255),ImColor(255,255,0,255),ImColor(0,255,0,255),ImColor(0,0,255,255),ImColor(128,0,128,255),ImColor(255,28,121,255) };
    ImColor ColRect;
    ColorsID ColorID;
    std::vector<Item> Items;
    bool runned = false;
    bool click = false;
    Item item;
    Item curItem;
    ImColor meanColor(enum ColorsID a, enum ColorsID b);
    myApp();
    void Init() override;
    void Update() override;
    void initOffset(ImVec2);
    ImVec2 WorldToScreen(const ImVec2 World);
    ImVec2 ScreenToWorld(const ImVec2 Screen);
    
};

