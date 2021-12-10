#ifndef GRAPHGEN_H
#define GRAPHGEN_H

#include "Graph.h"

using namespace std;

class GraphGen : public Graph{
    public:
        GraphGen();
        //utilities
        Graph* GenG(string inputFileName);


        // public functions
        void InsertVertex(int num, Graph* G);
        void InsertEdge(int a, int b, Graph* G);
        int Lookup(int num);
        void InOrder();
        void PreOrder(); 
};




#endif