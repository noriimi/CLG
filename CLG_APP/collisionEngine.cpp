#include "collisionEngine.h"
int collisionEngine::doStuff()
{
	out.clear();
	in.clear();
	bool flag = false;
	bool overlap = false;
	if (!overlap)
	{
		for (auto& i : input)
		{
			if (!overlap)
			{
				auto& a_2 = i;
				for (auto& j : input)
				{
					if (overlap)
						break;
					auto& b_2 = j;
					if (a_2== b_2)
						continue;
					if (doOverlap(a_2, b_2))
					{
						overlap = true;
						auto h = calcOverlap(a_2, b_2);
						if (h.area())
						{
							ImVec2 a, b, c, d;
							flag = false;
							a = h.topLeft;
							c = h.bottomRight;
							b = { c.x,a.y };
							d = { a.x,c.y };
							Item a1, a2, a3, a4, b1, b2, b3, b4;
							a1 = { a_2.topLeft,{a_2.bottomRight.x,b.y},a_2.color };
							a2 = { {a_2.topLeft.x,d.y }, a_2.bottomRight, a_2.color };
							a3 = { {a_2.topLeft.x,a.y}, d,a_2.color };
							a4 = { b,{a_2.bottomRight.x,c.y},a_2.color };
							b1 = { b_2.topLeft,{b_2.bottomRight.x,b.y},b_2.color };
							b2 = { {b_2.topLeft.x,d.y}, b_2.bottomRight,b_2.color };
							b3 = { {b_2.topLeft.x,a.y}, d,b_2.color };
							b4 = { b,{b_2.bottomRight.x,c.y},b_2.color };

							Item temp;
							if (a1.area())
							{
								flag = true;
								a1.id = ++id;
								temp = { {a1} };
								in.push_back({ temp });
							}
							if (a2.area())
							{
								flag = true;
								a2.id = ++id;
								temp = { {a2} };
								in.push_back({ temp });

							}
							if (a3.area())
							{
								flag = true;
								a3.id = ++id;
								temp = { {a3} };
								in.push_back({ temp });
							}
							if (a4.area())
							{

								flag = true;
								a4.id = ++id;
								temp = { {a4} };
								in.push_back({ temp });
							}
							if (b1.area())
							{

								flag = true;
								b1.id = ++id;
								temp = { {b1} };
								in.push_back({ temp });
							}
							if (b2.area())
							{
								flag = true;
								b2.id = ++id;
								temp = { {b2} };
								in.push_back({ temp });

							}
							if (b3.area())
							{
								flag = true;
								b3.id = ++id;
								temp = { {b3} };
								in.push_back({ temp });

							}
							if (b4.area())
							{
								flag = true;
								b4.id = ++id;
								temp = { {b4} };
								in.push_back({ temp });
							}

							collisions.push_back({ h });
							//in.push_back(h);
							if (flag)
							{
								out.push_back(a_2);
								out.push_back(b_2);

							}
						}
					}
				}
			}
		}
	}
	for (auto& i : out)
	{
		input.erase(i);
	}
	input.insert(in.cbegin(), in.cend());

	if (flag && overlap)
		return 1;
	return 0;
}

collisionEngine::collisionEngine(std::vector<Item>& v)
{
	for (auto& it : v)
	{
		it.id = ++id;
		input.insert(it);
	}
}

std::vector<Item> collisionEngine::getCollisions()
{
	return {collisions.cbegin(),collisions.cend()};
}

std::vector<Item> collisionEngine::getRest()
{
	return { input.cbegin(),input.cend() };
}

int collisionEngine::run()
{
	int c = 0;
	int a = 1;
	while (a)
	{
		a = doStuff();
		c++;
	}
	return c;
}



bool collisionEngine::doOverlap(ImVec2 l1, ImVec2 r1, ImVec2 l2, ImVec2 r2)
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
Item collisionEngine::calcOverlap(Item a, Item b)
{
	ImVec2 a1, a2;
	a1 = { std::max(a.topLeft.x, b.topLeft.x), std::max(a.topLeft.y, b.topLeft.y) };
	a2 = { std::min(a.bottomRight.x, b.bottomRight.x),std::min(a.bottomRight.y, b.bottomRight.y) };
	Item c = { a1 , a2,a.color };
	return c;
}
bool collisionEngine::doOverlap(Item a, Item b)
{
	/*if (a == b)
		return false;*/
	return doOverlap(a.topLeft, a.bottomRight, b.topLeft, b.bottomRight);
}