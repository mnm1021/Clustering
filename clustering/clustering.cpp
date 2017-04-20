#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <ctime>
#include "Dot.h"
#include "DBSCAN.h"
#include "k_means.h"

using namespace std;

vector<Dot*> get_input(FILE* fp);
void print_result(map< int, vector<Dot*> > clusters, char input_num);

int main(int argc, char** argv)
{
	FILE* fp_input, fp_output;
	int num_clusters;
	vector<Dot*> input_dots;
	map< int, vector<Dot*> > clusters;

	if (argc != 3)
	{
		printf("usage : cluster.exe [input_file] [num_of_clusters]\n");
		exit(-1);
	}

	srand(time(NULL));

	/* handle argv's. */
	fp_input = fopen(argv[1], "r");
	num_clusters = atoi(argv[2]);

	/* read from file, close file pointer. */
	input_dots = get_input(fp_input);
	fclose(fp_input);

	/* get clusters using k-means or dbscan algorithm. */
	switch (argv[1][5])
	{
	case '1':
		clusters = dbscan(input_dots, 14.88, 21, num_clusters);
		break;
	case '2':
		clusters = dbscan(input_dots, 1.766, 5, num_clusters);
		break;
	case '3':
		clusters = dbscan(input_dots, 2.0, 5, num_clusters);
		break;
	default:
		clusters = k_means(input_dots, num_clusters);
	}

	/* print result */
	print_result(clusters, argv[1][5]);

	return 0;
}

/********* I/O functions **********/

/*
 * get dots from input file.
 */
vector<Dot*> get_input(FILE* fp)
{
	vector<Dot*> input_dots;
	int id;
	double x, y;
	char buf[100];

	while (feof(fp) == 0)
	{
		fgets(buf, 100, fp);
		sscanf(buf, "%d\t%lf\t%lf", &id, &x, &y);
		Dot* new_dot = new Dot(id, x, y);
		input_dots.push_back(new_dot);
	}

	return input_dots;
}

/*
 * print every clusters.
 */
void print_result(map< int, vector<Dot*> > clusters, char input_num)
{
	char filename[22];
	memset(filename, 0, sizeof(filename));
	memcpy(filename, "output#_cluster_#.txt\0", 22);
	filename[6] = input_num;

	for (map< int, vector<Dot*> >::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		filename[16] = it->first + '0';
		FILE* fp = fopen(filename, "w");
		for (vector<Dot*>::iterator vec_it = it->second.begin(); vec_it != it->second.end(); vec_it++)
			fprintf(fp, "%d\n", (*vec_it)->id);
		fclose(fp);
	}
}