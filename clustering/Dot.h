#pragma once
#define NOISE -2
#define NONE -1

class Dot
{
public:
	Dot(int _id, double _x, double _y);
	~Dot();

	int id;
	double x, y;
	bool is_visited;
	int cluster_id; /* includes NOISE, NONE */

	bool is_dot_in_range(Dot dot, double range);
	double distance_powered_2(Dot dot);
};

