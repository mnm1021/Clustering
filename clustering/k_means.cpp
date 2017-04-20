#include "k_means.h"
#include "Cluster.h"

using namespace std;

/*
 * create cluster through 'k_means' algorithm.
 */
map< int, vector<Dot*> > k_means(vector<Dot*>& dataset, int k)
{
	map< int, vector<Dot*> > ret_clusters;
	Cluster *clusters;
	int cluster_id;
	bool dot_added = true;
	bool *is_added;

	/* create k clusters. */
	clusters = new Cluster[k];
	int* indexes = generate_random_dot(dataset, k);

	for (cluster_id = 0; cluster_id < k; cluster_id++)
	{
		clusters[cluster_id].init(dataset[indexes[cluster_id]], cluster_id);
		printf("cluster [%d] created : (%lf, %lf)\n", cluster_id, dataset[indexes[cluster_id]]->x, dataset[indexes[cluster_id]]->y);
	}
	delete indexes;

	/* add new point to each clusters. when any clusters didn't change, end loop. */
	is_added = new bool[k];
	for (cluster_id = 0; cluster_id < k; cluster_id++)
	{
		is_added[cluster_id] = true;
	}
	while (dot_added)
	{
		dot_added = false;
		for (cluster_id = 0; cluster_id < k; cluster_id++)
		{
			if (is_added[cluster_id] == false)
				continue;

			is_added[cluster_id] = clusters[cluster_id].add_nearest_dot(dataset);
			dot_added |= is_added[cluster_id];
		}
	}

	for (cluster_id = 0; cluster_id < k; cluster_id++)
	{
		ret_clusters[cluster_id] = clusters[cluster_id].dots;
	}

	//delete clusters;
	delete is_added;

	return ret_clusters;
}

/*
 * random dot generator from dataset.
 */
int* generate_random_dot(vector<Dot*>& dataset, int size)
{
	int* indexes = (int*)malloc(sizeof(int) * size);
	int i = 0;

	for (vector<Dot*>::iterator it = dataset.begin(); /* */; /* */)
	{
		if (rand() % 20 == 3)
			indexes[i++] = (*it)->id;

		if (i == size)
			break;

		/* advance to next dot. */
		it++;
		if (it == dataset.end())
			it = dataset.begin();
	}

	return indexes;
}