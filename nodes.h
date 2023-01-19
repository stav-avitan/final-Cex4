#ifndef nodes
#define nodes

typedef struct edge_ edge, *pedge;

// Node struct
typedef struct node_
{
    int id;
    pedge edges;
    struct node_ *next;
} node, *pnode;

node *newNode1(int);
void insertLastN(int, pnode *);
void deleteFromListN(int, node **);
pnode getNode (pnode *, int);
void deleteGraph(pnode *);

#endif