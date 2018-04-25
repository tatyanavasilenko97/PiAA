#include <iostream>
#include <vector>
#define SIZE 26

using namespace std;

void PrintMatrix(vector<vector<float>>& matrix){
    //cout << ' ';
    //for (char i = 'a'; i <= 'z'; i++)    cout << i;
    cout << endl;
    for(int i = 0; i < matrix.size(); ++i){
        //cout << char('a' + i);
        for(int j = 0; j < matrix.size(); ++j){
            cout << matrix[i][j] << ", ";
        }
        cout << endl;
    }
}

float MaxElement(vector<vector<float>>& matrix){
    float max = matrix[0][0];
    for (int i=0; i < SIZE; ++i){
        for (int j=0; j < SIZE; ++j){
            if (matrix[i][j] > max)    max = matrix[i][j];
        }
    }
    return max;
}

int Greedy(vector<vector<float>>& matrix, vector <char>& result, char& start, char& finish){
    int count = 0;
    int vertex = start - 'a';
    int end_vertex = finish - 'a';
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
            for (int i = 1;i < SIZE; ++i)    result[i] = 0;
            count = 0;
            vertex = start - 'a';
        }
        else {
            matrix[result[count - 1] - 'a'][vertex] = 0;
            result[count] = vertex + 'a';
        }
    }
    return count;
}

int main(){
    vector<vector <float>> matrix(SIZE, vector <float> (SIZE));// матрица смежности
    char start;// начальная вершина
    char finish;// конечная вершина
    char vertex1, vertex2;
    float weight;// вес
    vector <char> result(SIZE);// выходные данные
    cout << "start -> end : ";
    cin >> start >> finish;
    result[0] = start;
    
    int i;// переменные для работы с векторами
    while (cin >> vertex1 >> vertex2 >> weight)
        matrix[vertex1 - 'a'][vertex2 - 'a'] = weight;//= matrix[vertex2 - 'a'][vertex1 - 'a'] = weight;
    cout << endl<<endl;
    //PrintMatrix(matrix);
    cout << endl<<endl;
    int count = Greedy(matrix, result, start, finish);
    for (i = 0; i <= count; ++i){
        cout << result[i];
    }
    cout << endl << endl;
    return 0;
}
