#include <iostream>
#include <list>
#include <fstream>
#include <set>

using namespace std;

struct Vertex;

struct Edge{
    const int maxFlow;
    int currentFlow;
    Vertex* const from;
    Vertex* const to;
    int availableToAddFlow(){
        return maxFlow-currentFlow;
    }
    int availableToSubFlow(){
        return currentFlow;
    }
};


struct Vertex{
    char n;
    Edge* edgeFromPrev;
    set<Edge*> out;
    set<Edge*> in;
    Vertex* prev(){
        return edgeFromPrev->to!=this?edgeFromPrev->to:edgeFromPrev->from;
    }
};

struct Comparator_edge {
    bool operator()(Edge* const &l,  Edge* const &r) const {
        if(l->from->n!=r->from->n)return l->from->n<r->from->n;
        return l->to->n<r->to->n;
    }
};

const int V=256;
Vertex vert[V];
set<Edge*,Comparator_edge> edges;
int startV;
int finishV;
int totalCurrent=0;

void read(istream& cin){
    for(int i=0;i<V;i++)vert[i].n=i;
    int numOfEdges;
    cin>>numOfEdges;cin.get();
    startV=cin.get();cin.get();
    finishV=cin.get();cin.get();

    for(int i=0;i<numOfEdges;i++){
        int v1=cin.get();cin.get();
        int v2=cin.get();cin.get();
        int cost;cin>>cost;
        auto * edge=new Edge{cost,0,&vert[v1],&vert[v2]};
        edges.insert(edge);
        vert[v1].out.insert(edge);
        vert[v2].in.insert(edge);
        cin.get();
    }
}

bool dfs(){
    list<Vertex*> queue;
    queue.push_back(&vert[startV]);
    while(!queue.empty()){
        Vertex* current=*queue.begin();
        if(current->n==finishV)return true;
        queue.pop_front();
        for(Edge* e:current->out){
            Vertex* next=e->to;
            if(e->availableToAddFlow()==0)continue;
            if(next->edgeFromPrev!= nullptr)continue;
            next->edgeFromPrev=e;
            queue.push_back(next);
        }
        for(Edge* e:current->in){
            Vertex* next=e->from;
            if(e->availableToSubFlow()==0)continue;
            if(next->edgeFromPrev!= nullptr)continue;
            next->edgeFromPrev=e;
            queue.push_back(next);
        }
    }
    return false;
}

int minFlow(){
    int minimum=INT32_MAX;
    Vertex* last=&vert[finishV];
    Vertex* start=&vert[startV];
    while (last!=start){
        if(last->edgeFromPrev->to==last)minimum= min(last->edgeFromPrev->availableToAddFlow(),minimum);
        else minimum= min(last->edgeFromPrev->availableToSubFlow(),minimum);
        last=last->prev();
    }
    return minimum;
}

void updateFlow(){
    int flow= minFlow();
    totalCurrent+=flow;
    Vertex* last=&vert[finishV];
    Vertex* start=&vert[startV];
    while (last!=start){
        Edge* fromPrev=last->edgeFromPrev;
        if(last->edgeFromPrev->to==last)fromPrev->currentFlow+=flow;
        else fromPrev->currentFlow-=flow;
        last=last->prev();
    }
}

void reInit(){
    for(Vertex& v:vert)v.edgeFromPrev= nullptr;
}


void fordFalkerson(){
    reInit();
    while(dfs()){
        updateFlow();
        reInit();
    }
}

void printResult(){
    cout<<totalCurrent<<endl;
    for(Edge* e:edges)cout<<e->from->n <<" "<<e->to->n <<" "<<e->currentFlow<<endl;
}

int main() {
    //ifstream cin("../input2.txt");if(!cin)exit(123);
    read(cin);
    fordFalkerson();
    printResult();
    return 0;
}