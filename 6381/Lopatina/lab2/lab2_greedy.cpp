#include <iostream>
using namespace std;
#define SIZE 26

int main() {
char first_string[3]; 
cin >> first_string[0] >> first_string[2];
char edge_l = 0;
char edge_r = 0;
double weight = 0;
char path[SIZE] = {0};
double adj_matr[SIZE][SIZE]= {0};

while (cin>> edge_l){
	cin>> edge_r ;
    cin >> weight;
	int i = edge_l - 'a';
	int j = edge_r - 'a';
	adj_matr[i][j] = weight;
    adj_matr[j][i] = weight;
}

int count = 0;
path[0] = first_string[0];
int temp_vertex = first_string[0]-'a';
int end = first_string[2]-'a';

while (temp_vertex!= end){
	int dist = 100;
	int i = temp_vertex;
	count++;
	for (int j = 0; j < SIZE; j++){
		if ((dist > adj_matr[i][j]) && (adj_matr[i][j]!=0)){
			dist = adj_matr[i][j];
			temp_vertex = j;
		}
	}
	if (dist == 100){
		count -= 2;
		int bad_temp_vertex = temp_vertex; 
		temp_vertex = path[count] - first_string[0];
		adj_matr[temp_vertex][bad_temp_vertex] = 0;
	}
	else {
        // for (int j = 0;j<26; j++)    // участок кода для запрета прохода по циклам
		// 	adj_matr[path[count-1] - 'a'][j] = 0;
		// for (int i = 0;i<26; i++)
		// 	adj_matr[i][path[count-1] - 'a'] = 0;
		adj_matr[path[count-1] - 'a'][temp_vertex] = 0;
        adj_matr[temp_vertex][path[count-1] - 'a'] = 0;
		path[count] = temp_vertex + 'a';
	}
}

for (int k =0; k<=count; k++)
	cout << path[k];

return 0;
}