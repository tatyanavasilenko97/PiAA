#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
// #define DEBUG
#define maxN 40

using namespace std;

// Печатает содержимое Table.
void printTable(const vector<vector<int>>& Table, int N)
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cout.width(3);
            cout << Table[i][j] << " ";
        }
        cout << endl;
    }
}

// Проверка на выход за пределы массива
bool isOutOfBounds(int x, int y, int width, int N)
{
    return ((width>(N-x)) || (width>(N-y)));
}

void removePart(vector<vector<int>>& Table, int N, int x, int y, int partNumber)
{
    for(int i = y; (i < N) && (Table[i][x]==partNumber); ++i)
    {
        for (int j = x; (j < N) && (Table[i][j]==partNumber); ++j)
        {
            Table[i][j]=0;
        }
    }
}

// N - размер столешницы, x,y - координаты части, width - ее размер, partNumber - номер
bool setPart(vector<vector<int>>& Table, int N, int x, int y, int width, int partNumber)
{
    if (isOutOfBounds(x, y, width, N)) return false;
    // if (!isFree(Table,x,y,width)) return false;
    for(int i = 0; i < width; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (!Table[y+i][x+j])
                Table[y+i][x+j]=partNumber;
            else
            {
                removePart(Table, N, x, y, partNumber);
                return false;
            }
        }
    }
    return true;
}

bool findFreeCell(vector<vector<int>>& Table, int N, int& x, int& y)
{
    while (Table[y][x]!=0)
    {
        if (x==N-1)
        {
            x=0;
            ++y;
        }
        else ++x;
        if (x>=N || y>=N)
            return false;
    }
    return true;
}

//
void buildPrime(vector<vector<int>>& Table, int N, int x, int y, int partNmbr, int& bestPartNmbr)
{
    if (partNmbr>bestPartNmbr) return;
    if (findFreeCell(Table, N, x, y)) // Если есть свободная клетка
    {
        for (int i = N-1; i > 0; --i)
        {
            if (setPart(Table, N, x, y, i, partNmbr)) // То пробуем для нее различные размеры детали
            {
                ++partNmbr;
                buildPrime(Table, N, x, y, partNmbr, bestPartNmbr); // И для каждого размера детали проходимся по остальным клеткам
                --partNmbr;
            }
            removePart(Table, N, x, y, partNmbr);
        }
    }
    else if ((partNmbr-1)<bestPartNmbr)
    {
        bestPartNmbr = partNmbr-1; // Потому что часть под номером partNmbr пристроить не удалось
        // bestTable = Table;
    }
}

void tryBetter(vector<vector<int>>& Table, int N, int x, int y, int partNmbr, int& bestPartNmbr, int avArea)
{
    if (partNmbr>bestPartNmbr) return;
    if (findFreeCell(Table, N, x, y)) // Если есть свободная клетка
    {
        for (int i = N-1; i > 0; --i)
        {
             if ((avArea-i*i)<0) return;
            if (setPart(Table, N, x, y, i, partNmbr)) // То пробуем для нее различные размеры детали
            {
                ++partNmbr;
                tryBetter(Table, N, x, y, partNmbr, bestPartNmbr, avArea-i*i); // И для каждого размера детали проходимся по остальным клеткам
                --partNmbr;
            }
            removePart(Table, N, x, y, partNmbr);
        }
    }
    else if ((partNmbr-1)<bestPartNmbr)
    {
        bestPartNmbr = partNmbr-1; // Потому что часть под номером partNmbr пристроить не удалось
        // bestTable = Table;
    }
}

// Возвращает размер части
int findPart(vector<vector<int>>& Table, int N, int& x, int& y, int K)
{
    while (Table[y][x]!=K)
    {
        if (x==N-1)
        {
            x=0;
            ++y;
        }
        else ++x;
        if (x>=N || y>=N)
            return false;
    }
    int i = 0;
    while (Table[y][x+i]==K)
    {
        if ((x+i)<N)
        {
            ++i;
        }
        else return --i;
    }
    return i;
}

void printParts(vector<vector<int>>& Table, int N, int partNmbr)
{
    int x, y, size;
    for(int i = 1; i <= partNmbr; ++i)
    {
        x = 0;
        y = 0;
        size = findPart(Table, N, x, y, i);
        cout << x+1 << " " << y+1 << " " << size << endl;
    }
}

int solve(vector<vector<int>>& Table, int N)
{
    if ((N%2)==0)
    {
        // cout << 4 << endl;
        // cout << 1       << " " << 1     << " " << N/2 << endl;
        // cout << 1       << " " << N/2+1 << " " << N/2 << endl;
        // cout << N/2+1   << " " << 1     << " " << N/2 << endl;
        // cout << N/2+1   << " " << N/2+1 << " " << N/2 << endl;
        return 4;
    }
    else if ((N%3)==0)
    {
        // int K = N/3;
        // cout << 6 << endl;
        // cout << 1       << " " << 1     << " " << 2*K << endl;
        // cout << 2*K+1   << " " << 1     << " " << K << endl;
        // cout << 2*K+1   << " " << K+1   << " " << K <<endl;
        // cout << 2*K+1   << " " << 2*K+1 << " " << K << endl;
        // cout << K+1     << " " << 2*K+1 << " " << K << endl;
        // cout << 1       << " " << 2*K+1 << " " << K << endl;
        return 6;
    }
    else if ((N%5)==0)
    {
        // int K=N/5;
        // cout << 8 << endl;
        // cout << 1       << " " << 1     << " " << 3*K << endl;
        // cout << 1+3*K   << " " << 1     << " " << 2*K << endl;
        // cout << 1+3*K   << " " << 1+2*K << " " << 2*K << endl;
        // cout << 1       << " " << 1+3*K << " " << 2*K << endl;
        // cout << 1+2*K   << " " << 1+3*K << " " << K   << endl;
        // cout << 1+2*K   << " " << 1+4*K << " " << K   << endl;
        // cout << 1+3*K   << " " << 1+4*K << " " << K   << endl;
        // cout << 1+4*K   << " " << 1+4*K << " " << K   << endl;
        return 8;
    }
    else
    {
        // Ставим заранее известные детали, сокращая "размеры" столешницы для вычислений примерно на 75%
        setPart(Table, N, 0, 0, N/2+1, 1);
        setPart(Table, N, N/2+1, 0, N/2, 2);
        setPart(Table, N, 0, N/2+1, N/2, 3);
        setPart(Table, N, N/2+1, N/2, 1, 4);
        int K = 40;
        buildPrime(Table, N, N/2+2, N/2, 5, K);
        removePart(Table, N, 0, 0, 1);
        removePart(Table, N, N/2+1, 0, 2);
        removePart(Table, N, 0, N/2+1, 3);
        removePart(Table, N, N/2+1, N/2, 4);
        return K;
    }
}

int main()
{
    int K1, K2;
    for(int i = 2; i <= 40; ++i)
    {

          K1 = 40;
          vector<vector<int>> Table(i, vector<int>(i,0)); // Инициализировали массив NxN нулями
          K1 = solve(Table, i);
          std::cout << "For N = " << i << ":\n" <<  "Answer of optimized algorithm is: " << K1 << std::endl;

          K2=K1;
          time_t t1 = time(0);
          tryBetter(Table, i, 0, 0, 1, K2, i*i);
          std::cout << "Answer of basic algorithm without optimizations trying to find lower number: " << K2 << std::endl;
          if (K1!=K2)
          {
               std::cout << "Answers are different!" << std::endl;
               break;
          }
          time_t t2 = time(0);
          std::cout << "Time needed for basic algorithm: " << t2-t1 << endl;
    }
    if (K1==K2)
         std::cout << "Optimized algorithm passed tests. " << std::endl;
    return 0;
}
