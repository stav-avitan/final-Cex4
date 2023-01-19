//
// Created by stavavitan on 1/19/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "nodes.h"
#include "edges.h"

#define MAX 1000000
void createNewGraph(pnode *h);
void addVertice(pnode *h);
void deleteVertice (pnode *h);
void delete_graph(pnode *h);
void shortsPath(pnode h);
int shortsPathWithMat(pnode h, int, int);
int min(int, int);
void TisTheShortestPath(pnode h);
void allChoices(pnode, int *, int, int , int *, int *);
int calc(pnode, int[], int);
void swap(int *, int *);
int numOfWays(int);
int findMinimum(int[], int);

void option (char answer, pnode *graph)
{
    switch (answer)
    {
        case 'A':
            createNewGraph(graph);
            break;

        case 'B':
            addVertice(graph);
            break;

        case 'D':
            deleteVertice (graph);
            break;

        case 'S':
            shortsPath(*graph);
            break;

        case 'T':
            TisTheShortestPath(*graph);
            break;

        default:
            if (answer == EOF)
            {
                return;
            }
    }
}

void createNewGraph(pnode *h)
{
    int numOfVertices = 0;
    scanf("%d", &numOfVertices);
    for (int i = 0; i < numOfVertices; i++)
    {
        insertLastN(i, h);
    }
    char p = 0;
    int ansOfp = scanf(" %c", &p);
    while (ansOfp != 0)
    {
        if (p == 'n')
        {
            int src = -1;
            scanf("%d", &src);
            int dest, weight;
            int destAns = scanf("%d", &dest);
            int weightAns = scanf("%d", &weight);
            while (destAns != 0 && weightAns != 0)
            {
                if (isalpha(dest))
                {
                    break;
                }
                addEdge(src, dest, weight, h);
            }
        }
        else
        {
            break;
        }
    }
    option(p, h);
}

void addVertice(pnode *h)
{
    int index;
    scanf("%d", &index);
    int dest, weight;
    pnode newNode1 = getNode(h, index);
    if (newNode1 == NULL)
    {
        insertLastN(index, h);
        int destAns = scanf("%d", &dest);
        int weightAns = scanf("%d", &weight);
        while (weightAns  != 0 && destAns  != 0)
        {
            if (isalpha(dest))
            {
                break;
            }
            else if (!(isalpha(dest))){
                addEdge(index, dest, weight, h);
            }

        }
    }
    else
    {
        pedge *pedge1 = &(newNode1->edges);
        freeEdges(pedge1);
        newNode1->edges = NULL;

        int destAns = scanf("%d", &dest);
        int weightAns = scanf("%d", &weight);

        while (weightAns  != 0 && destAns  != 0)
        {
            if (isalpha(dest))
            {
                break;
            }
            else if (!(isalpha(dest))){
                addEdge(index, dest, weight, h);
            }
        }
    }
    option(getchar(), h);
}

void delete_graph(pnode* h)
{
    if (!h)
    {
        return;
    }
    pnode t = *h;
    while (t)
    {
        pedge newNodeOfEdges = t->edges;
        while (newNodeOfEdges)
        {
            pedge newEdge = newNodeOfEdges;
            newNodeOfEdges = newNodeOfEdges->next;
            free(newEdge);
        }
        pnode node = t;
        t = t->next;
        free(node);
    }
    free(t);
}

void deleteVertice(pnode *h)
{
    int index;
    scanf("%d", &index);

    pnode t = *h;
    while (t)
    {
        pedge *tempPedge = &(t->edges);
        deleteFromListE(index, tempPedge, h);
        t = t->next;
    }
    deleteFromListN(index, h);
    option (getchar(), h);
}

void shortsPath(pnode h)
{
    int src = 0, dst = 0;
    scanf("%d", &src);
    scanf("%d", &dst);
    printf("Dijsktra shortest path: %d \n", shortsPathWithMat(h, src, dst));
}

int shortsPathWithMat(pnode h, int source, int target)
{
    if (!h)
    {
        return -1;
    }
    pnode current = h;
    int largestNode = 0;
    while (current)
    {
        if (largestNode < current->id)
        {
            largestNode = current->id;
        }
        current = current->next;
    }
    largestNode += 1;
    int matrix[largestNode][largestNode];

    for (int k = 0; k < largestNode; k++)
    {
        for (int i = 0; i < largestNode; i++)
        {
            matrix[k][i] = MAX;
        }
    }

    current = h;
    while (current)
    {
        pedge ed = current->edges;
        while (ed)
        {
            matrix[current->id][ed->endpoint->id] = ed->weight;
            ed = ed->next;
        }
        current = current->next;
    }

    for (int k = 0; k < largestNode; k++)
    {
        for (int i = 0; i < largestNode; i++)
        {
            for (int j = 0; j < largestNode; j++)
            {
                if (i == j)
                {
                    matrix[i][i] = 0;
                }
                else if (j == k || i == k)
                {
                    matrix[i][j] = matrix[i][j];
                }
                else
                {
                    int val = matrix[i][k] + matrix[k][j];
                    if (matrix[i][k] == 0 || matrix[k][j] == 0)
                    {
                        val = 0;
                    }
                    matrix[i][j] = min(matrix[i][j], val);
                }
            }
        }
    }
    if (matrix[source][target] == MAX)
    {
        return -1;
    }
    return matrix[source][target];
}

int min(int x, int y) {
    if (x == 0) {
        return y;
    } else {
        if (y == 0) {
            return x;
        } else {
            if (x < y) {
                return x;
            }
            return y;
        }
    }
}

void TisTheShortestPath(pnode h)
{
    int numOfVertices;
    scanf("%d", &numOfVertices);
    if (numOfVertices == 0)
    {
        return;
    }
    int vertices[numOfVertices];
    for (size_t i = 0; i < numOfVertices; i++)
    {
        scanf("%d", &vertices[i]);
    }
    int ways = numOfWays(numOfVertices);
    int newVertices[ways];
    int t = 0;
    allChoices (h, vertices, 0, numOfVertices - 1, newVertices, &t);
    int newMinIndex = findMinimum(newVertices, ways);
    if (newVertices[newMinIndex] == MAX)
    {
        printf("TSP shortest path: %d \n", -1);
    }
    else
    {
        printf("TSP shortest path: %d \n", newVertices[newMinIndex]);
    }
}

int calc(pnode h, int vertices[], int size)
{
    int distanceBetweenVertices = 0;
    for (size_t i = 0; i < size - 1; i++)
    {
        int path = shortsPathWithMat(h, vertices[i], vertices[i + 1]);
        if (path == -1)
        {
            return MAX;
        }
        distanceBetweenVertices += path;
    }
    return distanceBetweenVertices;
}

void swap(int *x, int *y)
{
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

void allChoices(pnode h, int *vertices, int start, int end, int *perm, int *ind)
{
    if (start == end)
    {
        perm[(*ind)++] = calc(h, vertices, end + 1);
        return;
    }
    int i;
    for (i = start; i <= end; i++)
    {
        swap((vertices + i), (vertices + start));
        allChoices(h, vertices, start + 1, end, perm, ind);
        swap((vertices + i), (vertices + start));
    }
}

int findMinimum(int arr[], int size)
{
    int minIndex = 0;
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[minIndex])
        {
            minIndex = i;
        }
    return minIndex;
}

int numOfWays(int vertices)
{
    if (vertices < 0){
        return 0;
    }
    if (vertices == 0){
        return 1;
    }
    return numOfWays (vertices - 1) * vertices;
}