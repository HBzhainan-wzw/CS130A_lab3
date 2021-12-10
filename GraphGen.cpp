#include "Graph.h"
#include "GraphGen.h"

using namespace std;

GraphGen::GraphGen(){
    // cout<<"graphGen"<<endl;

}





// public functions
void GraphGen::InsertVertex(int num, Graph* G){
    // 1. look for number
    node* target = G->Lookup(num, G->avlTreeRoot);
    // if exist, return
    if(target) return;
    // else insert
    //cout<<"inserting Vertex "<< num <<endl;
    G->avlTreeRoot = G->InsertVertex(G->avlTreeRoot, num);
    if(num > G->maxMember) G->maxMember = num;
    G->memberCnt++;
}
void GraphGen::InsertEdge(int a, int b, Graph* G){
    //cout<<"inserting edge "<< a << "--"<< b <<endl;
    node* a1 = G->Lookup(a, G->avlTreeRoot);
    node* a2 = G->Lookup(b, G->avlTreeRoot);
    if(!a1) InsertVertex(a, G);
    if(!a2) InsertVertex(b, G);
    G->InsertEdge(a, a2);
    G->InsertEdge(b, a1);
}


//utilities
Graph* GraphGen::GenG(string inputFileName){
    Graph* G = new Graph(); // create a graph

    // utility variable
    string line;
    ifstream dataFile(inputFileName.c_str());
    string a,b;
    int c,d;
    
    while(getline(dataFile,line)){
        // load two numbers
        // split two number
        int i = 0;
        for(i = 0; i < line.length();i++){
            if (line[i] == ',') break;
        }
        a = line.substr(0,i);
        b = line.substr(i+1,line.length());
            // cout<< "a = "<< a <<endl;
            // cout<< "b = "<< b <<endl;
        c = stoi(a);
        d = stoi(b);
        // insert vertex
        InsertVertex(c, G);
        //cout<< "==="<<endl;
        //G->PreOrder(G->avlTreeRoot);
        //cout<<endl;
        //cout<< "==="<<endl;
        InsertVertex(d, G);
        //cout<< "==="<<endl;
        //G->PreOrder(G->avlTreeRoot);
        //cout<<endl;
        //cout<< "==="<<endl;
        // insert edge
        InsertEdge(c, d, G);
    }
    // cout<<"The in order traversal:"<<endl;
    // // cout<<"root check"<<(avlTreeRoot==NULL)<<endl;
    // G->InOrder(G->avlTreeRoot);
    // cout<<endl;
    // cout<<"The pre order traversal:"<<endl;
    // G->PreOrder(G->avlTreeRoot);
    // cout<<endl;
    // cout<<"Is acyclic(Yes/No):"<<endl;
    // if(G->acyclic) cout<<"Yes"<<endl;
    // if(!G->acyclic) cout<<"No"<<endl;
    // cout<<"adr: "<<G->avlTreeRoot<<endl;
    // cout<<"value: "<<G->avlTreeRoot->data<<endl;
    return G;
}
