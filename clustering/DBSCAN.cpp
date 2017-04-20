#include "DBSCAN.h"

using namespace std;

/******* functions for DBSCAN *******/

/*
* true if given 'dot' is in 'dataset', false if isn't.
*/
bool is_dot_in_dataset(vector<Dot*> dataset, Dot dot)
{
	for (vector<Dot*>::iterator it = dataset.begin(); it != dataset.end(); it++)
		if ((*it)->id == dot.id)
			return true;
	return false;
}

/*
* get 'neighbor' dots : dots that are within 'range'.
*/
vector<Dot*> get_neighbor_dots(vector<Dot*> dataset, Dot dot, double range)
{
	vector<Dot*> neighbor_dots;

	for (vector<Dot*>::iterator it = dataset.begin(); it != dataset.end(); it++)
		if (dot.is_dot_in_range(**it, range))
			neighbor_dots.push_back(*it);

	return neighbor_dots;
}

/*
* get a cluster from dataset, including given 'dot'.
*/
vector<Dot*> get_cluster(vector<Dot*>& dataset, Dot* dot, vector<Dot*> neighbor_dots, int cluster_id, double range, int minimum_dots)
{
	vector<Dot*> cluster;
	vector<Dot*> curr_neighbor_dots, tmp_neighbor_dots;
	curr_neighbor_dots = neighbor_dots;

	/* add dot to current cluster. */
	dot->cluster_id = cluster_id;
	cluster.push_back(dot);

	/* loop through all current neighbor dots. */
	while (curr_neighbor_dots.size() > 0)
	{
		for (vector<Dot*>::iterator it = curr_neighbor_dots.begin(); it != curr_neighbor_dots.end(); it++)
		{
			/* if dot is not visited, set dot to visited and check neighbors. */
			if ((*it)->is_visited == false)
			{
				(*it)->is_visited = true;
				vector<Dot*> new_neighbor_dots = get_neighbor_dots(dataset, **it, range);

				/* if num of neighbors not lower than minimum, add new neighbors. */
				if (new_neighbor_dots.size() >= minimum_dots)
				{
					for (vector<Dot*>::iterator new_it = new_neighbor_dots.begin(); new_it != new_neighbor_dots.end(); new_it++)
						if (is_dot_in_dataset(neighbor_dots, **new_it) == false)
						{
							neighbor_dots.push_back(*new_it);
							tmp_neighbor_dots.push_back(*new_it);
						}
				}
			}

			/* put to current cluster if dot's cluster_id is NONE. */
			if ((*it)->cluster_id == NONE)
			{
				//printf("dot [%d] (%lf, %lf) added to cluster [%d]\n", (*it)->id, (*it)->x, (*it)->y, cluster_id);
				(*it)->cluster_id = cluster_id;
				cluster.push_back(*it);
			}
		}

		curr_neighbor_dots = tmp_neighbor_dots;
		tmp_neighbor_dots.clear();
	}

	return cluster;
}

/*
* returns 'map' of clusters using DBSCAN algorithm.
*/
map< int, vector<Dot*> > dbscan(vector<Dot*>& dataset, double range, int minimum_dots, int num_clusters)
{
	map< int, vector<Dot*> > clusters;
	int cluster_id = 0;

	/* sweep through all dots in 'dataset'. */
	for (vector<Dot*>::iterator it = dataset.begin(); it != dataset.end(); it++)
	{
		/* if dot is already visited, continue. */
		if ((*it)->is_visited)
			continue;

		/* check dot into 'visited'. */
		(*it)->is_visited = true;

		/* get dot's neighbors. */
		vector<Dot*> neighbor_dots = get_neighbor_dots(dataset, **it, range);

		/* if neighbors are less then minimum, check to NOISE. else, create new cluster. */
		if (neighbor_dots.size() < minimum_dots)
			(*it)->cluster_id = NOISE;
		else
		{
			printf("creating cluster [%d] : \n", cluster_id);
			vector<Dot*> cluster = get_cluster(dataset, *it, neighbor_dots, cluster_id, range, minimum_dots);
			clusters[cluster_id] = cluster;
			cluster_id++;
		}

		if (cluster_id == num_clusters)
			break;
	}

	return clusters;
}