#pragma once
#include "ColorsID.h"
#include "imgui.h"
class Item
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
    void calculateDiagonal();
};

