#include <iostream>
#include <fstream>
using namespace std;
const int SIZE = 'z' - 'a'+1;
const double MAX =10000000;

double lable[SIZE];
double m[SIZE][SIZE];
bool isVisited[SIZE];
int prevV[SIZE];
int start,finish;
void read(istream& cin){
    start=cin.get()-(int)'a';
    cin.get();
    finish=cin.get()-(int)'a';
    cin.get();
    while(true){
        int v1=cin.get()-(int)'a';
        cin.get();
        int v2=cin.get()-(int)'a';
        cin.get();
        double cost;
        cin>>cost;
        if(cin.eof())return;
        cin.get();
        m[v1][v2] = cost;
        m[v2][v1] = cost;
    }
}

void print(int finish_v){
    if (start==finish_v){
        cout<<(char)(start+'a');
        return;
    }
    print(prevV[finish_v]);
    cout<<(char)(finish_v+'a');

}

int main() {
    ifstream ifs("../input6.txt");if(!ifs)exit(123);

    //cin>>start;
    //cin>>finish;

    //start = 'a';
    //finish = 'd';

    int minIndex ;
    double minL ;
    for (int i = 0;i<SIZE;i++)
        for (int j = 0;j<SIZE;j++) {
            m[i][j] = 0;
        }
    //
    //matrix input
    //


    read(ifs);
    for (int i = 0;i<SIZE;i++){
        lable[i] = MAX;
        isVisited[i] = false;
    }
    lable[start] = 0;
    //prevV[start] = -1;
    do{
        minL = MAX;
        minIndex = SIZE;
        for (int i = 0;i<SIZE;i++)
            if(lable[i]+((finish-i)) < minL+((finish-minIndex)) && !isVisited[i]) {
                minL =lable[i];
                minIndex = i;
            }
        if (minL!=MAX) {
            for (int i = 0; i < SIZE; i++)
                if (m[minIndex][i]!=0 && m[minIndex][i]+minL<lable[i]){
                    lable[i]=m[minIndex][i]+minL;
                    prevV[i]=minIndex;
                }
        }
        isVisited[minIndex]= true;
    } while (minIndex != SIZE);
    print(finish);
    //cout<<lable[(int)finish - (int)'a'];
    //cout<<lable[finish];

}