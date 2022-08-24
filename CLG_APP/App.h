#pragma once
void App();
void initApp();
void initOffset(ImVec2);
struct ITEM
{
public:
    int color;
    ImVec2 start, end;
    int id;
    void convert();
    int area();
};
