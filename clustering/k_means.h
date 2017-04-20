#pragma once
#include <map>
#include <vector>
#include "Dot.h"

std::map< int, std::vector<Dot*> > k_means(std::vector<Dot*>& dataset, int k);
int* generate_random_dot(std::vector<Dot*>& dataset, int size);