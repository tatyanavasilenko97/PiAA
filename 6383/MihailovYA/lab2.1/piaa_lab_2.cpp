#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class WayTo{
public:
    char from,to;
    float weight;
    bool correct;
    WayTo(): from('\0'), to('\0'), weight(0), correct(true){}
    WayTo(char _from, char _to, double _weight): from(_from), to(_to), weight(_weight), correct(true){}
};

int Solution(vector<WayTo> &way, char a, int k, vector<char> &answer,vector<char> &visited){
    WayTo min;
    for (int i = 0; i < way.size(); i++)
        if ((way[i].from == a) && (way[i].correct)) {min = way[i]; k = i; break;}
        
        
        
    if (min.weight == 0.0f)
     {
    
        way[k].correct = false; return -1;
     }

    for (int i = 0; i < way.size(); i++){
        if ((way[i].weight < min.weight) && (way[i].from == a) && (way[i].correct) && (find(visited.begin(), visited.end(), way[k].to) == answer.end())) 
        {
                min = way[i]; k = i;
                
        }
    }
    
    
    
    if (find(answer.begin(), answer.end(), way[k].to) != answer.end() ) 
    {
        way[k].correct = false; 
        return -1;
    }
    return k;
}

int main(){
    char a, b;
    cin >> a >> b;
    vector<WayTo> way;
    //WayTo currway;
    char tmp,tmp2;
    
    float weight;
    while (tmp2 != b ){
        cin >> tmp >> tmp2 >> weight;
        WayTo currway(tmp, tmp2, weight);
        way.push_back(currway);
    }
    char curr = a;
    int i = 0,prev=0;
    vector<char> sequence;
    vector<char> visited;
    int sum=0;
    while(true){
        
        i = Solution(way, curr, i, sequence,visited);
        
        if (i == -1) {
                i = 0;
                curr = way[i].from;
                sum-=way[i].weight;
                sequence.clear();
        }
        else {
        sequence.push_back(curr);
        visited.push_back(way[i].from);
        sum+=way[i].weight;
        prev=i;
        curr = way[i].to;
        
        }
        if (way[i].to == b) break;
    }
    if(i!=0) sequence.push_back(b);
    
    for (int i = 0; i<sequence.size(); i++)
        cout << sequence[i];
        //cout << sum<<"--"<<endl;
}
