#include <iostream>
#include <queue>
#define SIZE 100
using namespace std;

int temp_flow[SIZE][SIZE]= {-1}; // текущий поток
int adj_matr[SIZE][SIZE]= {0}; // матрица пропускных способностей

int find_path (char istock, char stock) { 
    int flow_vert [SIZE] = {0}; // значение потока через данную вершину на данном шаге поиска
    char came_from [SIZE] = {0}; // массив значений, откуда мы пришли
    queue <char> Q; // очередь вершин 
    char temp_vert; //текущая вершина
    flow_vert [(int)(istock-'1')] = 1000; 
    came_from[(int)(stock-'1')] = 0;
    Q.push(istock);
    
    while (came_from[(int)(stock-'1')] == 0 && !Q.empty()) { 
        temp_vert = Q.front(); 
         for (int j = 0; j < SIZE; j++){
                if ((adj_matr[(int)(temp_vert - '1')][j] - temp_flow[(int)(temp_vert - '1')][j])>0 && flow_vert[j] == 0) {
                        Q.push((char)(j+'1'));
                        came_from[j] = temp_vert;
                        flow_vert[j] = min(flow_vert[(int)(temp_vert-'1')], adj_matr[(int)(temp_vert - '1')][j] 
                        - temp_flow[(int)(temp_vert - '1')][j]);
                }
         }
        Q.pop();
    }

    if (came_from[(int)(stock-'1')] == 0)
        return 0; 
       
    temp_vert = stock;
    while ( temp_vert!=istock ) {
         temp_flow [(int)(came_from[(int)(temp_vert-'1')]- '1')][(int)(temp_vert-'1')] += flow_vert [(int)(stock-'1')];
         temp_flow [(int)(temp_vert-'1')][(int)(came_from[(int)(temp_vert-'1')]- '1')] -= flow_vert [(int)(stock-'1')];
         temp_vert = came_from [(int)(temp_vert-'1')];
    }
    return flow_vert [(int)(stock-'1')]; 
}

int max_flow (char istock, char stock) {
    int new_flow = find_path(istock, stock);
    int m_flow = new_flow;
    while (new_flow>0){
        new_flow = find_path(istock, stock);
        m_flow += new_flow;
    }
    return m_flow;
}

int main() {
int number_edges = 0;
cin >> number_edges;
char stock, istock, vert_left, vert_right;
int throughput; //пропускная способность
cin >> istock;
cin >> stock;
for (int k = 0; k < number_edges; k++){
    cin >> vert_left >> vert_right >> throughput;
    int i = vert_left - '1';
	int j = vert_right- '1';
	adj_matr[i][j] = throughput;
}

int max_flow_m = max_flow (istock,stock);
cout << max_flow_m << endl;
for (int i = 0; i<SIZE; i++){
    for (int j = 0; j< SIZE; j++){
        if (temp_flow[i][j]!= -1 && temp_flow[i][j] < 0 )
            temp_flow[i][j] = 0;
        if ((temp_flow[i][j]!=-1)&&adj_matr[i][j]!=0)
            cout << (char)(i+'1') << ' ' << (char)(j+'1') << ' ' << temp_flow[i][j] << endl;
    }
}
return 0;
}