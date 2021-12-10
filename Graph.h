#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;


struct node{
    int data;
    vector<int> adjList;
    node* left;
    node* right;
    int height;
};

class Graph{
    public:
        vector<bool> visited;
        vector<int> arr;
        vector<int> dep;
        int compCnt = 0;
        vector<vector<int>> components;
        
    
        vector<pair<int,int>> pastTrace;
        bool acyclic = true;
        node* avlTreeRoot = NULL;
        int maxMember = 0;
        int memberCnt = 0;
        int time = -1;
        //constructors
        Graph();
        Graph(vector<node> avlTree);

        //public functions
        node* InsertVertex(node* n, int num);
        void InsertEdge(int target, node* adr);
        node* Lookup(int num, node* root);
        void InOrder(node* root);
        void PreOrder(node* root); 

        // utilities
        node* newNode(int num);
        node* rightRotate(node* n);
        node* leftRotate(node* n);
        int checkBalance(node* n);
        int getMax(int a, int b);
        int getHeight(node* n);
        void InOrderTrav(node* root);
        void report();
        void addTrace(int a, int b);
        bool checkTrace(int a, int b);

        //find acyclic
        // DFSculmul : driver for DFS, finding #components and cycles
        void DFSculmul();
        void DFS(int v);

};



#endif