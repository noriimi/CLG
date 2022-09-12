#pragma once
#include <unordered_set>
#include "Item.h"
template<> struct std::hash<item>
{
	std::size_t operator()(const item& p) const noexcept
	{
		return p(p);
	}
};
class collision_engine
{
private:
	std::unordered_set<item> input_;
	std::vector<item> collisions_;
	static bool do_overlap(ImVec2 l1, ImVec2 r1, ImVec2 l2, ImVec2 r2);
	[[nodiscard]] item calc_overlap(item a, item b) const;
	static bool do_overlap(item a, item b);
	int collide();
	int id_ = 0;
	std::vector<item> in_, out_;
public:
	std::vector<item> rest_;
	static bool is_inside(item a, item b);
	int do_stuff();
    collision_engine()=default;
	explicit collision_engine(std::vector<item>& v);
	[[nodiscard]] std::vector<item> get_collisions() const;
	[[nodiscard]] std::vector<item> get_rest() const;
    int run();
	int cleanup();
};

