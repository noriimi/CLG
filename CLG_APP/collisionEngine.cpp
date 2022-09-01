#include "collisionEngine.h"
auto collision_engine::do_stuff() -> int
{
	out_.clear();
	in_.clear();
	bool flag = false;
	bool overlap = false;
	if (!overlap)
	{
		for (auto& i : input_)
		{
			if (!overlap)
			{
				auto& a_2 = i;
				for (auto& j : input_)
				{
					if (overlap)
						break;
					auto& b_2 = j;
					if (a_2== b_2)
						continue;
					if (do_overlap(a_2, b_2))
					{
						overlap = true;
						if (auto h = calc_overlap(a_2, b_2); h.area())
						{
							ImVec2 a, b, c, d;
							flag = false;
							a = h.top_left;
							c = h.bottom_right;
							b = { c.x,a.y };
							d = { a.x,c.y };
							item a1, a2, a3, a4, b1, b2, b3, b4;
							a1 = { a_2.top_left,{a_2.bottom_right.x,b.y},a_2.color };
							a2 = { {a_2.top_left.x,d.y }, a_2.bottom_right, a_2.color };
							a3 = { {a_2.top_left.x,a.y}, d,a_2.color };
							a4 = { b,{a_2.bottom_right.x,c.y},a_2.color };
							b1 = { b_2.top_left,{b_2.bottom_right.x,b.y},b_2.color };
							b2 = { {b_2.top_left.x,d.y}, b_2.bottom_right,b_2.color };
							b3 = { {b_2.top_left.x,a.y}, d,b_2.color };
							b4 = { b,{b_2.bottom_right.x,c.y},b_2.color };

							item temp;
							if (a1.area())
							{
								flag = true;
								a1.id = ++id_;
								temp = { {a1} };
								in_.push_back({ temp });
							}
							if (a2.area())
							{
								flag = true;
								a2.id = ++id_;
								temp = { {a2} };
								in_.push_back({ temp });

							}
							if (a3.area())
							{
								flag = true;
								a3.id = ++id_;
								temp = { {a3} };
								in_.push_back({ temp });
							}
							if (a4.area())
							{

								flag = true;
								a4.id = ++id_;
								temp = { {a4} };
								in_.push_back({ temp });
							}
							if (b1.area())
							{

								flag = true;
								b1.id = ++id_;
								temp = { {b1} };
								in_.push_back({ temp });
							}
							if (b2.area())
							{
								flag = true;
								b2.id = ++id_;
								temp = { {b2} };
								in_.push_back({ temp });

							}
							if (b3.area())
							{
								flag = true;
								b3.id = ++id_;
								temp = { {b3} };
								in_.push_back({ temp });

							}
							if (b4.area())
							{
								flag = true;
								b4.id = ++id_;
								temp = { {b4} };
								in_.push_back({ temp });
							}

							collisions_.push_back({ h });
							//in.push_back(h);
							if (flag)
							{
								out_.push_back(a_2);
								out_.push_back(b_2);

							}
						}
					}
				}
			}
		}
	}
	for (auto& i : out_)
	{
		input_.erase(i);
	}
	input_.insert(in_.cbegin(), in_.cend());

	if (flag && overlap)
		return 1;
	return 0;
}

collision_engine::collision_engine(std::vector<item>& v)
{
	for (auto& it : v)
	{
		it.id = ++id_;
		input_.insert(it);
	}
}

std::vector<item> collision_engine::get_collisions() const
{
	return {collisions_.cbegin(),collisions_.cend()};
}

std::vector<item> collision_engine::get_rest() const
{
	return { input_.cbegin(),input_.cend() };
}

int collision_engine::run()
{
	int c = 0;
	int a = 1;
	while (a)
	{
		a = do_stuff();
		c++;
	}
	return c;
}



bool collision_engine::do_overlap(const ImVec2 l1, const ImVec2 r1, const ImVec2 l2, const ImVec2 r2)
{
	// if rectangle has area 0, no overlap
	if (l1.x == r1.x || l1.y == r1.y || r2.x == l2.x || l2.y == r2.y)
		return false;

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y <= l2.y || r2.y <= l1.y)
		return false;

	return true;
}
item collision_engine::calc_overlap(const item a, const item b) const
{
	const ImVec2 a1 = {std::max(a.top_left.x, b.top_left.x), std::max(a.top_left.y, b.top_left.y)};
	const ImVec2 a2 = {std::min(a.bottom_right.x, b.bottom_right.x), std::min(a.bottom_right.y, b.bottom_right.y)};
	const item c = { a1 , a2,a.color };
	return c;
}
bool collision_engine::do_overlap(const item a, const item b)
{
	/*if (a == b)
		return false;*/
	return do_overlap(a.top_left, a.bottom_right, b.top_left, b.bottom_right);
}