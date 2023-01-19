//
// Created by stavavitan on 1/19/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "edges.h"
#include "graph.h"

void addEdge(int , int , int , pnode *);
void insertLastE(pnode, int , pnode *);
void deleteFromListE(int, pedge *, pnode *);
void freeEdges(pedge *);
edge *newEdge(int , pnode);

edge *newEdge(int weight, pnode dest)
{
    edge *e = (edge *)malloc(sizeof(edge));
    if (e == NULL)
    {
        return NULL;
    }
    e->weight = weight;
    e->endpoint = dest;
    e->next = NULL;
    return e;
}

void insertLastE(pnode dest, int w, pnode *head)
{
    pedge e = (*head)->edges;
    pedge ed = newEdge(w, dest);
    if (!e)
    {
        (*head)->edges = ed;
    }
    else
    {
        while (e->next)
        {
            e = e->next;
        }
        e->next = ed;
    }
}

void addEdge(int src, int dest, int w, pnode *head)
{
    pnode curr = *head;
    pnode nsrc = NULL;
    pnode ndest = NULL;

    while (curr)
    {
        if (curr->id == src)
        {
            nsrc = curr;
        }
        if (curr->id == dest)
        {
            ndest = curr;
        }
        curr = curr->next;
    }

    if (!nsrc || !ndest)
    {
        return;
    }

    insertLastE(ndest, w, &nsrc);
}

void deleteFromListE(int id, pedge *h, pnode *n)
{
    if (!*h)
        return;
    pedge p = *h;
    pedge *prev = h;
    while (p)
    {
        if (p->endpoint->id == id)
        {
            *prev = p->next;
            free(p);
            p = *prev;
        }
        else
        {
            prev = &(p->next);
            p = p->next;
        }
    }
}

void freeEdges(pedge *edge)
{
    if (!edge)
    {
        return;
    }
    pedge e = *edge;
    pedge *prev = edge;
    while (e)
    {
        *prev = e->next;
        free(e);
        e = *prev;
    }
}