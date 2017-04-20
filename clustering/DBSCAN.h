#pragma once
#include <vector>
#include <map>
#include "Dot.h"

/* DBSCAN functions */
std::vector<Dot*> get_neighbor_dots(std::vector<Dot*> dataset, Dot dot, double range);
std::vector<Dot*> get_cluster(std::vector<Dot*>& dataset, Dot* dot, std::vector<Dot*> neighbor_dots, int cluster_id, double range, int minimum_dots);
std::map< int, std::vector<Dot*> > dbscan(std::vector<Dot*>& dataset, double range, int minimum_dots, int num_clusters);
bool is_dot_in_dataset(std::vector<Dot*> dataset, Dot dot);