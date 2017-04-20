#include "Dot.h"
#include <cmath>
#include <cstdio>

Dot::Dot(int _id, double _x, double _y)
{
	id = _id;
	x = _x;
	y = _y;
	is_visited = false;
	cluster_id = NONE;
}


Dot::~Dot()
{
}

bool Dot::is_dot_in_range(Dot dot, double range)
{
	return distance_powered_2(dot) <= pow(range, 2);
}

/*
 * return the 'SQUARED' distance between given 'dot' and this dot.
 */
double Dot::distance_powered_2(Dot dot)
{
	return pow(dot.x - x, 2) + pow(dot.y - y, 2);
}