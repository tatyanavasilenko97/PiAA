#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <map>
#include <stack>

using namespace std;

struct Info {
    Info(char name, float weight): name(name), weight(weight) {};
	
    char name;
    float weight;
};

class Vertex {
public:
    Vertex(char name) : name(name){};

    char get_name() const {
        return name;
    }
	
	list<Info> list_edge;// список всевозможных путей, в другие вершины + вес
private:
    char name;
};

class Info_prior {// приоритет для приоритетной очереди
public:
    Info_prior(Vertex vert, float prior): vert(vert), prior(prior){};
    
	bool operator <(const Info_prior b) const {
        return prior > b.prior;
    }
	
	Vertex vert;
    float prior;
};

class Adjacency_list {
public:
    Adjacency_list() {
        for (char i = 'a'; i <= 'z'; i++)
            list_vertex.push_back(Vertex(i));
    }
    
    Vertex& at(char a){
        return list_vertex[a - 'a'];
    }
	
	float heuristic(Info temp, Vertex last) {
        return abs(last.get_name() - temp.name);
    }
	
    void search_result (Vertex first, Vertex last) {
		queue.emplace(first, 0);

		prevV_nextV[first.get_name()] = first.get_name();
		vertex_to_weight[first.get_name()] = 0;

		while(!queue.empty()) {
			const Vertex temp = queue.top().vert;
			queue.pop();

			if(temp.get_name() == last.get_name()) 
				break;

			for(const Info& next : at(temp.get_name()).list_edge) {
				float new_weight = vertex_to_weight[temp.get_name()] + next.weight;
				if((vertex_to_weight.find(next.name) == vertex_to_weight.end()) || (new_weight < vertex_to_weight[next.name])) {
					vertex_to_weight[next.name] = new_weight;
					float priority = new_weight + heuristic(next, last);
					prevV_nextV[next.name] = temp.get_name();
					queue.emplace(at(next.name), priority);  
				}
			}
		}
		print_result(first, last, prevV_nextV);
    }
	
	void print_result(Vertex first, Vertex last, map<char, char>& prevV_nextV){
		stack<char> result;
		char element = last.get_name();
		result.push(element);
		while(element != first.get_name()) {
			element = prevV_nextV[element];
			result.push(element);
		}
		while (!result.empty()){
			cout << result.top();
			result.pop();
		}
	}
	
	priority_queue<Info_prior> queue;// приоритетная очередь
	vector<Vertex> list_vertex; 
    map <char, char> prevV_nextV; 
    map <char, float> vertex_to_weight; 
};

int main(){
	char f_vertex;// начальная вершина
	char l_vertex;// конечная вершина
	char vertex1, vertex2;
	float weight;// вес
	
	Adjacency_list adjacency_list;
	
	cin >> f_vertex >> l_vertex;
	Vertex first_vertex (f_vertex);
	Vertex last_vertex (l_vertex);
	
	while (cin >> vertex1 >> vertex2 >> weight)
		adjacency_list.at(vertex1).list_edge.push_back({vertex2, weight});
	
	
	adjacency_list.search_result(first_vertex, last_vertex);
	
	return 0;
}

