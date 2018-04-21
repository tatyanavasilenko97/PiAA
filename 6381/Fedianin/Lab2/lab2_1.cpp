#include <iostream>
#include <vector>
#define SIZE 26

using namespace std;

void PrintMatrix(vector<vector<float>>& matrix);
int GreedyAlgorithm(vector<vector<float>>& matrix, vector <char>& result, char& f_vertex, char& l_vertex);
float MaxElement(vector<vector<float>>& matrix);

int main(){
	vector<vector <float>> matrix(SIZE, vector <float> (SIZE));// матрица смежности
	char f_vertex;// начальная вершина
	char l_vertex;// конечная вершина
	char vertex1, vertex2;
	float weight;// вес
	vector <char> result(SIZE);// выходные данные
	
	cin >> f_vertex >> l_vertex;
	result[0] = f_vertex;
	
	int i,j;// переменные для работы с векторами
	while (cin >> vertex1 >> vertex2 >> weight)	
		matrix[vertex1 - 'a'][vertex2 - 'a'] = weight;//= matrix[vertex2 - 'a'][vertex1 - 'a'] = weight;
	
	//PrintMatrix(matrix);
	
	int count = GreedyAlgorithm(matrix, result, f_vertex, l_vertex);
	for (i = 0; i <= count; ++i)	cout << result[i];
	//PrintMatrix(matrix);	
	return 0;
}

void PrintMatrix(vector<vector<float>>& matrix){
	cout << ' ';
	for (char i = 'a'; i <= 'z'; i++)	cout << i;
	cout << endl;
	for(int i = 0; i < matrix.size(); ++i){
		cout << char('a' + i);
			for(int j = 0; j < matrix.size(); ++j){
				cout << matrix[i][j];	
			}
		cout << endl;
	}
}

int GreedyAlgorithm(vector<vector<float>>& matrix, vector <char>& result, char& f_vertex, char& l_vertex){
	int count = 0;
	int vertex = f_vertex - 'a';
	int end_vertex = l_vertex - 'a';
	while (vertex != end_vertex){
		float min = (MaxElement(matrix) + 1);
		float test = min;
		int i = vertex;
		count++;
		for (int j = 0; j < SIZE; j++){
			if ((min > matrix[i][j]) && (matrix[i][j] != 0)){
				min = matrix[i][j];
				vertex = j;
			}
		}
		if (min == test){
			matrix[result[count - 2] - 'a'][vertex] = 0;
			for (int i = 1;i < SIZE; ++i)	result[i] = 0;
			count = 0;
			vertex = f_vertex - 'a';
			//cout << "&&&&" << vertex << "&&&&" << endl;
			//PrintMatrix(matrix);
		}
		else {
			matrix[result[count - 1] - 'a'][vertex] = 0;
			result[count] = vertex + 'a';
			//PrintMatrix(matrix);
		}
	}
	return count;
}

float MaxElement(vector<vector<float>>& matrix){
	float max = matrix[0][0];
	for (int i=0; i < SIZE; ++i){
      for (int j=0; j < SIZE; ++j){
         if (matrix[i][j] > max)	max = matrix[i][j];
      }
   }
   return max;	
}
