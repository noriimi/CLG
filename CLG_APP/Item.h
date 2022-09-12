#pragma once
#include "ColorsID.h"
#include "imgui.h"
#include <iostream>
class item
{
public:
	colors_id color;
    ImVec2 start, end;
    ImVec2 one, two;
    ImVec2 top_left, bottom_right,top_right,bottom_left;
    int id;
    bool collision;
    void convert();
    [[nodiscard]] float area() const;
    [[nodiscard]] float area2() const;
    friend bool operator==(const item& lhs, const item& rhs);
    bool operator<(const item& rhs) const;
    void calculate();
    item();
    item(ImVec2 start, ImVec2 end, colors_id color);
    friend std::ostream& operator<<(std::ostream& os, const item& obj);
    size_t operator()(const item& rhs) const {
	    const size_t hash = rhs.id;
        return hash;
    };
private:
    void calculate_diagonal();
};