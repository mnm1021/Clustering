#pragma once
#include <vector>
#include "Dot.h"

class Cluster
{
public:
	Cluster();
	~Cluster();

	void init(Dot* dot, int id);
	bool Cluster::add_nearest_dot(std::vector<Dot*>& dataset);
	void add_dot(Dot* new_dot);
	void set_center();

	std::vector<Dot*> dots;
	Dot center;
	int cluster_id;
};

