#pragma once
#include "ColorsID.h"
#include "imgui.h"
#include <cmath>
#include <iostream>
class Item
{
public:
    enum ColorsID color;
    ImVec2 start, end;
    ImVec2 one, two;
    ImVec2 topLeft, bottomRight,topRight,bottomLeft;
    int id;
    void convert();
    float area() const;
    float area2();
    friend bool operator==(const Item& lhs, const Item& rhs);
    bool operator<(const Item& rhs);
    void calculate();
    Item();
    Item(ImVec2 start_, ImVec2 end_, enum ColorsID color_);
    friend std::ostream& operator<<(std::ostream& os, const Item& obj);
    size_t operator()(const Item& rhs) const {
        size_t hash = rhs.id;
        return hash;
    };
private:
    void calculateDiagonal();
};