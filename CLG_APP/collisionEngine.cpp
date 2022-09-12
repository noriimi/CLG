#include "collisionEngine.h"
bool collision_engine::is_inside(const item a, const item b)
{
	const bool a1 = a.start.x >= b.start.x && a.start.y >= b.start.y;
	const bool b1 = a.end.x <= b.end.x && a.end.y <= b.end.y;
	const bool c1 = b.start.x >= a.start.x && b.start.y >= a.start.y;
	const bool d1 = b.end.x <= a.end.x && b.end.y <= a.end.y;
	const bool e1 = (a1 && b1) || (c1 && d1);
	return e1;
}
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
					if (a_2 == b_2)
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
							b = h.top_right;
							d = h.bottom_left;
							item a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
							a1 = { {h.top_left.x,a_2.top_left.y},h.top_right,a_2.color };

							a2 = { h.bottom_left, {h.bottom_right.x,a_2.bottom_right.y}, a_2.color };

							a3 = { {a_2.top_left.x,h.top_left.y}, h.bottom_left,a_2.color };

							a4 = { h.top_right,{a_2.bottom_right.x,h.bottom_right.y},a_2.color };

							b1 = { {h.top_left.x,b_2.top_left.y},h.top_right,b_2.color };

							b2 = { h.bottom_left, {h.bottom_right.x,b_2.bottom_right.y}, b_2.color };

							b3 = { {b_2.top_left.x,h.top_left.y}, h.bottom_left,b_2.color };

							b4 = { h.top_right,{b_2.bottom_right.x,h.bottom_right.y},b_2.color };

							c1 = { a_2.top_left,h.top_left,a_2.color };

							c2 = { {h.top_right.x,a_2.top_right.y},{a_2.bottom_right.x,h.top_right.y},a_2.color };

							c3 = { {a_2.bottom_left.x,h.bottom_left.y},{h.top_left.x,a_2.bottom_left.y},a_2.color };

							c4 = { h.bottom_right, a_2.bottom_right, a_2.color};

							d1 = { b_2.top_left,h.top_left,b_2.color };

							d2 = { {h.top_right.x,b_2.top_right.y},{b_2.bottom_right.x,h.top_right.y},b_2.color };

							d3 = { {b_2.bottom_left.x,h.bottom_left.y},{h.top_left.x,b_2.bottom_left.y},b_2.color };

							d4 = { h.bottom_right, b_2.bottom_right, b_2.color };
							item temp;
							h.id = ++id_;
							h.collision = true;
							temp = { {h} };
							collisions_.push_back({ temp });
							in_.push_back({ temp });
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
							if (c1.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								c1.id = ++id_;
								temp = { {c1} };
								in_.push_back({ temp });
							}
							if (c2.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								c2.id = ++id_;
								temp = { {c2} };
								in_.push_back({ temp });
							}
							if (c3.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								c3.id = ++id_;
								temp = { {c3} };
								in_.push_back({ temp });
							}
							if (c4.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								c4.id = ++id_;
								temp = { {c4} };
								in_.push_back({ temp });
							}
							if (d1.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								d1.id = ++id_;
								temp = { {d1} };
								in_.push_back({ temp });
							}
							if (d2.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								d2.id = ++id_;
								temp = { {d2} };
								in_.push_back({ temp });
							}
							if (d3.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								d3.id = ++id_;
								temp = { {d3} };
								in_.push_back({ temp });
							}
							if (d4.area() && (is_inside(a_2, b_2) || is_inside(b_2, a_2)))
							{
								flag = true;
								d4.id = ++id_;
								temp = { {d4} };
								in_.push_back({ temp });
							}
							
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
	return { collisions_.cbegin(),collisions_.cend() };
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
		std::cout << std::endl << std::endl;
		for(auto &it:input_)
		{
			std::cout << std::boolalpha;
			std::cout << it << '\t' << it.id <<'\t'<<it.collision<< std::endl;
		}
	}
	a = 1;
	erase_if(input_, [](const item itt) {return itt.collision; });
	cleanup();
	std::cout << std::endl << std::endl;
	for (auto& it : collisions_)
	{
		std::cout << std::boolalpha;
		std::cout << it << '\t' << it.id << '\t' << it.collision << std::endl;
	}

	std::cout << std::endl << std::endl;
	for (auto& it : input_)
	{
		std::cout << std::boolalpha;
		std::cout << it << '\t' << it.id << '\t' << it.collision << std::endl;
	}
	return c;
}

int collision_engine::cleanup()
{
	int b = 0;
	std::vector<item> out;
	for (const auto& it : collisions_)
	{
		for (auto& i : input_)
		{
			if (do_overlap(it, i))
			{
				out.push_back(i);
				b++;
			}
		}
	}
	for (auto& i : out)
	{
		input_.erase(i);
	}
	return b;
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
	const ImVec2 a1 = { std::max(a.top_left.x, b.top_left.x), std::max(a.top_left.y, b.top_left.y) };
	const ImVec2 a2 = { std::min(a.bottom_right.x, b.bottom_right.x), std::min(a.bottom_right.y, b.bottom_right.y) };
	const item c = { a1 , a2,a.color };
	return c;
}
bool collision_engine::do_overlap(const item a, const item b)
{
	/*if (a == b)
		return false;*/
	return do_overlap(a.top_left, a.bottom_right, b.top_left, b.bottom_right);
}