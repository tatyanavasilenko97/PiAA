#include <iostream>
#include <fstream>
using namespace std;
const int SIZE = 'z' - 'a'+1;
const double MAX =10000000;

double lable[SIZE];
double m[SIZE][SIZE];
bool isVisited[SIZE];
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
    }
}
int main() {
    ifstream ifs("../input.txt");if(!ifs)exit(123);

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
    do{
        minL = MAX;
        minIndex = SIZE;
        for (int i = 0;i<SIZE;i++)
            if(lable[i] < minL && !isVisited[i]) {
                minL =lable[i];
                minIndex = i;
            }
        if (minL!=MAX) {
            for (int i = 0; i < SIZE; i++)
                if (m[minIndex][i]!=0 && m[minIndex][i]+minL<lable[i]){
                    lable[i]=m[minIndex][i]+minL;
                }
        }
        isVisited[minIndex]= true;
    } while (minIndex != SIZE);
    //cout<<lable[(int)finish - (int)'a'];
    //cout<<lable[finish];
    char path[SIZE];
    int tmp = finish;
    path[0] = (char)(finish+'a');
    int k = 0;
    double weigth = lable[tmp];
    //cout<<lable[1]<< m[1][tmp]<<lable[tmp];
    while (tmp>0){
        for (int i=0;i<SIZE;i++)
            if( weigth-m[i][tmp] == lable[i]){
                weigth = lable[i];
                tmp = i;
                k++;
                path[k] = (char)(i + (int)'a');
            }
    }
    for (int i = k;i>=0;i--)
        cout<<path[i];
    return 0;
}