#include <iostream>
#include <cfloat>
#include <fstream>
#include <list>
#include <vector>
#include <set>

using namespace std;

const int V=50;
const double INFINITY= DBL_MAX*2;
int startV;
int finishV;

struct Vertex;

struct Edge{
    const double w;
    Vertex* const to;
};

struct Vertex{
    int n;
    double pathFromStart=INFINITY;
    double h;
    Vertex* prevBestVertex= nullptr;
    list<Edge> e;
    double f(){
        return h+pathFromStart;
    }
};

struct Comparator_aStar {
    bool operator()(Vertex * const &l,  Vertex * const &r) const {
        return l->f() < r->f();
    }
};

struct Comparator_deicstra {
    bool operator()(Vertex * const &l,  Vertex * const &r) const {
        return l->pathFromStart < r->pathFromStart;
    }
};

Vertex vert[V];


void read(istream& cin){
    for(int i=0;i<V;i++)vert[i].n=i;
    startV=cin.get()-'a';
    cin.get();
    finishV=cin.get()-'a';
    cin.get();
    vert[startV].pathFromStart=0;
    while(true){
        int v1=cin.get()-'a';
        cin.get();
        int v2=cin.get()-'a';
        cin.get();
        double cost;
        cin>>cost;
        vert[v1].e.push_back({cost,&vert[v2]});
        vert[v1].h=finishV-v1;
        vert[v2].e.push_back({cost,&vert[v1]});
        vert[v2].h=finishV-v2;
        if(cin.eof())return;
        cin.get();
    }
}

void findPath(){
    std::multiset<Vertex*,Comparator_aStar> queue;
    for(Vertex& v:vert)queue.insert(&v);
    while(!queue.empty()){
        Vertex* current=*queue.begin();
        if(current->n==finishV)return;
        queue.erase(queue.begin());
        for(Edge& e:current->e){
            if(e.to->pathFromStart>e.w+current->pathFromStart){
                queue.erase(e.to);
                e.to->pathFromStart=e.w+current->pathFromStart;
                e.to->prevBestVertex=current;
                queue.insert(e.to);
            }
        }
    }
}

void printResult(Vertex* start,Vertex* finish){
    if(start==finish){
        cout<<(char)(start->n+'a');
        return;
    }
    printResult(start,finish->prevBestVertex);
    cout<<(char)(finish->n+'a');
}

int main() {
    //ifstream ifs("../input6.txt");if(!ifs)exit(123);
    read(cin);
    findPath();
    printResult(&vert[startV],&vert[finishV]);
    return 0;
}