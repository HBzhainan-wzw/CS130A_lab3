#include "Graph.h"
using namespace std;
// constructors
Graph::Graph(){

}
Graph::Graph(vector<node> avlTree){


}

// utilities
node* Graph::newNode(int num){
    node* n = new node();
    n->data = num;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

int Graph::getMax(int a, int b){
    return (a > b) ? a : b;
}

node* Graph::rightRotate(node* n){
    // store pointers
    node* leftChild = n->left;
    node* leftChildBr = leftChild->right;
    //rotate
    leftChild->right = n;
    n->left = leftChildBr;
    //update heights
    n->height = getMax(getHeight(n->left), getHeight(n->right)) + 1;
    leftChild->height = getMax(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;
 
    // Return new root
    return leftChild;
}

node* Graph::leftRotate(node* n){
    // store pointers
    node* rightChild = n->right;
    node* rightChildBr = rightChild->left;
    //rotate
    rightChild->left = n;
    n->right = rightChildBr;
    //update heights
    n->height = getMax(getHeight(n->left), getHeight(n->right)) + 1;
    rightChild->height = getMax(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;
 
    // Return new root
    return rightChild;
}

int Graph::getHeight(node* n){
    if(!n) return 0;
    return n->height;
}

int Graph::checkBalance(node* n){
    if(!n) return 0;
    return (getHeight(n->left) - getHeight(n->right));
}





// DFS functions
void Graph::DFSculmul(){
    // initializing vectors
    maxMember++;
    vector<bool> a(maxMember, false);
    visited = a;
    vector<int> b(maxMember, 0);
    arr = b;
    dep = b;
    // for each vertex in graph do
    InOrderTrav(avlTreeRoot);
}
void Graph::DFS(int v){
    //increment time
    time++;
    arr[v] = time; //record arrive time
    //cout<< "v: " << v << " arr[v]: " << arr[v] <<endl;
    components[compCnt].push_back(v);
    visited[v] = true;
    int adjNode = 0;
    node* adr = Lookup(v, avlTreeRoot);
    
    for(int i = 0; i < adr->adjList.size(); i++){
        int data = adr->adjList[i];
        adjNode = data; // for each adjacent node
        if(!visited[adjNode]){
            //cout<< "go to "<<adjNode<<endl;
            addTrace(v,adjNode);
            DFS(adjNode);
        } // if not visited do DFS
    }
    //cout<< "leave from: "<<v<<endl;
    time++;
    //record depart time
    dep[v] = time;
    //cout<< "v: " << v << " dep[v]: " << dep[v] <<endl;
    // looking for back edge
    // for each edge, check arr and dep time
    for(int i = 0; i < adr->adjList.size(); i++){
        adjNode = adr->adjList[i];
        
        if(arr[adjNode] > arr[v] && dep[adjNode] < dep[v] && !checkTrace(v,adjNode)){ // if backedge
            //cout<<"back Edge!" << "v : "<< v << " arr[v]: " << arr[v] << " dep[v]: " << dep[v] << " adjNode: " << adjNode << " arr[u]: " << arr[adjNode] << " dep[u]: " << dep[adjNode]<<  endl;
            acyclic = false; 
            break;
        }
    }

}
void Graph::addTrace(int a, int b){
    pair<int,int> temp (b,a);
    if(a > b){
         temp = pair<int,int>(b,a);
    }else{
        temp = pair<int,int>(a,b);
    }
    pastTrace.push_back(temp);
}
bool Graph::checkTrace(int a, int b){
    int x,y;
    if(a>b){
        x = b;
        y = a;
    }else{
        x = a;
        y = b;
    }
    for(int i = 0; i < pastTrace.size(); i++){
        if (pastTrace[i].first == x && pastTrace[i].second == y){
            return true;
        }
    }
    return false;
}
void Graph::InOrderTrav(node* root){
    if(!root) return;
    int v = root->data;
    InOrderTrav(root->left);
    
    if(!visited[v]){
        //cout<<"DFS: "<< v <<endl;
        vector<int> a;
        components.push_back(a);
        DFS(v);
        compCnt++; // increment component
    }    
    InOrderTrav(root->right);
}
void Graph::report(){
    cout<<"The in order traversal:"<<endl;
    InOrder(this->avlTreeRoot);
    cout<<endl;
    cout<<"The pre order traversal:"<<endl;
    PreOrder(this->avlTreeRoot);
    cout<<endl;
    cout<<"Is acyclic(Yes/No):"<<endl;
    if(acyclic) cout<<"Yes"<<endl;
    if(!acyclic) cout<<"No"<<endl;
    cout<<"Connected Components:"<<endl;
    for(int i = 0; i < compCnt; i++){
        for(int j = 0; j < components[i].size(); j++){
            sort(components[i].begin(),components[i].end());
            cout<<components[i][j]<<" ";
        }
        cout<<endl;
    }
}
void Graph::InOrder(node* root){
    if(!root) return;
    InOrder(root->left);
    cout<<root->data<<" ";
    InOrder(root->right);
}
void Graph::PreOrder(node* root){
    if(!root) return;
    cout<<root->data<<" ";
    PreOrder(root->left);
    PreOrder(root->right);
} 





// public functions
node* Graph::InsertVertex(node* n, int num){
    // start insertion
    // 1. if spot empty, assign new node in the correct spot
    if(!n){
        // cout<< "found spot"<<endl;
        return newNode(num);
    }  
    // 2. BST insertion
    // find the correct spot
    if (num < n->data){
        // cout<< "going left"<<endl;
        n->left = InsertVertex(n->left, num); // go to left child
    } 
    if (num > n->data){
        // cout<< "going right"<<endl;
        n->right = InsertVertex(n->right, num); // go to right child
    }
    // as a node inserted in the path, increment each node's height by one
    //cout<< "updating height"<<endl;
    n->height = 1 + getMax(getHeight(n->left), getHeight(n->right));
    // check validity by comparing the height difference between two children
    //cout<< "checking balance" << endl;
    int flag = checkBalance(n);
    // four cases
    // left left
    if(flag > 1 && num < n->left->data){
        //cout<< "left left"<<endl;
        return rightRotate(n);
    } 
    // right right 
    if(flag < -1 && num > n->right->data){
        //cout<< "right right"<<endl;
        return leftRotate(n);
    }
    // left right
    if(flag > 1 && num > n->left->data){
        //cout<< "left right"<<endl;
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    // right left 
    if(flag < -1 && num < n->right->data){
        //cout<< "right left"<<endl;
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
    // cout<< "end" << endl;
    return n;
}

void Graph::InsertEdge(int target, node* adr){
    if(!adr) return;
    for(int i = 0; i < adr->adjList.size(); i++){
        // if already have, return
        if(adr->adjList[i] == target) return;
    }
    // if dont have, add it to the adjList
    adr->adjList.push_back(target);
    sort(adr->adjList.begin(),adr->adjList.end());
}

node* Graph::Lookup(int num, node* root){
    //cout<<"Look up: "<< num<<endl;
    if(!root){
        return NULL;
    }
    int Data = root->data;
    if(Data == num){
        return root;
    }
    if(num > Data){
        return Lookup(num, root->right);
    }else{
        return Lookup(num, root->left);
    }
    return NULL;
}

