#include "Cluster.h"

using namespace std;

/******* 'Cluster' class for k_means *******/

Cluster::Cluster() : center(-1, -1, -1)
{
}


Cluster::~Cluster()
{
}

void Cluster::init(Dot* dot, int id)
{
	add_dot(dot);
	dot->cluster_id = id;
	cluster_id = id;
}

/*
 * add the nearest dot in dataset that is not in this cluster.
 */
bool Cluster::add_nearest_dot(vector<Dot*>& dataset)
{
	Dot* nearest_dot = NULL;
	double nearest_distance = -1;

	/* search for the nearest dot. */
	for (vector<Dot*>::iterator it = dataset.begin(); it != dataset.end(); it++)
	{
		if ((*it)->cluster_id != cluster_id)
		{
			double distance = center.distance_powered_2(**it);
			if (nearest_dot == NULL || nearest_distance > distance)
			{
				nearest_dot = *it;
				nearest_distance = distance;
			}
		}
	}

	if (nearest_dot == NULL || nearest_distance == -1)
		return false;

	if (nearest_dot->cluster_id == NONE)
	{
		//printf("dot [%d] (%lf, %lf) added to cluster [%d]\n", nearest_dot->id, nearest_dot->x, nearest_dot->y, cluster_id);
		add_dot(nearest_dot);
		nearest_dot->cluster_id = cluster_id;
		return true;
	}
	else
		return false;
}

void Cluster::add_dot(Dot* new_dot)
{
	dots.push_back(new_dot);
	set_center();
}

void Cluster::set_center()
{
	double x = 0, y = 0;

	for (vector<Dot*>::iterator it = dots.begin(); it != dots.end(); it++)
	{
		x += (*it)->x;
		y += (*it)->y;
	}

	x /= dots.size();
	y /= dots.size();

	center.x = x;
	center.y = y;
}