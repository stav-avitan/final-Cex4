#ifndef GRAPH_
#define GRAPH_

#include "nodes.h"
#include "edges.h"

void delete_graph(pnode *h);
void createNewGraph(pnode *h);
void addVertice(pnode *h);
void deleteVertice (pnode *h);
void shortsPath(pnode h);
int shortsPathWithMat(pnode h, int, int);
int min(int, int);
void TisTheShortestPath(pnode h);
void allChoices(pnode, int *, int, int , int *, int *);
int calc(pnode, int[], int);
void swap(int *, int *);
int numOfWays(int);
int findMinimum(int[], int);

void option (char, pnode *head);


#endif
