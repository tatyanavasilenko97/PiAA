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

int min(vector<way> &graph, char start, int k, vector<char> answer, vector<char> &visited){ 
way min; 
for (int i = 0; i < graph.size(); i++) 
if ((graph[i].from == start) && (graph[i].correct)) {min = graph[i]; k = i; break;} 

if (min.weight == 0) {graph[k].correct = false; return -1;} 

for (int i = 0; i < graph.size(); i++) 
if ((graph[i].weight < min.weight) && (graph[i].from == start) && (graph[i].correct) && (find(visited.begin(), visited.end(), graph[k].to)== answer.end())) {min = graph[i]; k = i;} 
if (find(answer.begin(), answer.end(), graph[k].to) != answer.end()) {graph[k].correct = false; return -1;} 
return k; 
} 

int main(){ 
char start, end; 
cin >> start >> end; 
vector<way> graph; 
vector<char> corrway;
vector<char> visited;
int sum=0; 
way currway; 
char temp = start; 
char temp1; 
double weight; 
while (temp1 != end){ 
cin >> temp >> temp1 >> weight; 
way currway(temp, temp1, weight); 
graph.push_back(currway); 
} 
char start1 = start; 
int i = 0, prev=0; 
for(;;){ 
//corrway.push_back(start1);//добавляем в конец очереди нашу стартовую букву 
i = min(graph, start1, i, corrway, visited); 
if (i == -1) {i = 0; start1 = graph[i].from; sum-=graph[i].weight; corrway.clear();} 
else 
{
	corrway.push_back(start1);
	visited.push_back(graph[i].from);
	sum+=graph[i].weight;
	prev=i;
	start1=graph[i].to;  
}
//start1 = graph[i].to; 
if (graph[i].to == end) break; 
} 
corrway.push_back(end); 

for (int i = 0; i<corrway.size(); i++) 
cout << corrway[i]; 
}
