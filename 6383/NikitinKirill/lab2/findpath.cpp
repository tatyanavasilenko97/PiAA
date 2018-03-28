#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class way{
public:
    char from;
    char to;
    double weight;
    bool correct;
    way(): from('\0'), to('\0'), weight(0), correct(true){};
    way(char from, char to, double weight): from(from), to(to), weight(weight), correct(true){}
};

int min(vector<way> &graph, char start, int k, vector<char> answer){
    way min;
    for (int i = 0; i < graph.size(); i++)
        if ((graph[i].from == start) && (graph[i].correct)) {min = graph[i]; k = i; break;}

    if (min.weight == 0) {graph[k].correct = false; return -1;}

    for (int i = 0; i < graph.size(); i++)
        if ((graph[i].weight < min.weight) && (graph[i].from == start) && (graph[i].correct)) {min = graph[i]; k = i;}
    if (find(answer.begin(), answer.end(), graph[k].to) != answer.end()) {graph[k].correct = false; return -1;}
    return k;
}

int main(){
    char start, end;
    cin >> start >> end;
    vector<way> graph;
    vector<char> answer;
    way currway;
    char temp = start;
    char temp1;
    double weight;
    while (temp1 != end){
        cin >> temp >> temp1 >> weight;
        way currway(temp, temp1, weight);
        graph.push_back(currway);
    }
    char current = start;
    int i = 0;
    while(true){
        answer.push_back(current);
        i = min(graph, current, i, answer);
        if (i == -1) {i = 0; current = start; answer.clear();}
        else current = graph[i].to;
        if (graph[i].to == end) break;
    }
    answer.push_back(end);
    
    for (int i = 0; i<answer.size(); i++)
        cout << answer[i];
}
