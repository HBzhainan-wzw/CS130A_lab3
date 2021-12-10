#include "GraphGen.h"

using namespace std;

int main(int argc, char* argv[]){

    string Filename = argv[1];
    ifstream inputFile(Filename);
    // call GraphGenerator
    GraphGen* graphGen = new GraphGen();
    Graph* graphOp = graphGen->GenG(Filename);
    graphOp->DFSculmul();
    graphOp->report();
}