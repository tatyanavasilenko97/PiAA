#include <iostream>
#include <vector>

using namespace std;

void Coloring(int x, int y, int size, int color, vector<vector<int> >& Table)
{//красим нужным цветом области квадрата
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            Table[i][j] = color;
}

int SearchEmptyArea(int last_x, int last_y, vector<vector<int> > & Table, int N)
{
    //поиск пустых клеток
    for (int j = last_y; j < N; j++)
    {
        if (Table[last_x][j] == 0)
            return last_x * 100 + j;//координаты ближайшей свободной ячейки
    }
    //поиск пустых клеток
    for (int i = last_x + 1; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Table[i][j] == 0)
                return i * 100 + j;//
        }
    }
    return -1;//если пустых больше нет
}

int Square(vector<vector<int> > & Table, vector<vector<int> > & Result, int N, int x, int y, int BestNum, int Current)
{
    int Point = 0;
    int MaxSize = N - 1;//максимальная сторона квадрата
    int ResultNum = 0;
    int y1 = y + 1;
    
    if (Current > BestNum)//если количество квадратов больше лучшего предыдущего результата, то дальше смотреть нет смысла
        return BestNum;
    
    while ((y1 < N) && (y1 >= 0))
    {//проверка на пересечение справа
        if (Table[x][y1] != 0)
        {//если будет перекрытие квадратов
            MaxSize = y1 - y;
            y1 = -2;
        }
        y1++;
    }
    if (y1 == N)//если выходит за пределы квадрата справа
        MaxSize = N - y;
    if ((N - x) < MaxSize)//если выходит за пределы квадрата снизу
        MaxSize = N - x;
    
    for (int i = 1; i <= MaxSize; i++)
    {
        Coloring(x, y, i, Current, Table);//красим нужную часть квадрата
        Point = SearchEmptyArea(x, y + i - 1, Table, N);//вызываем поиск точки
        if (Point >= 0) {//если точка есть, то рекурсивно вызываем новую функцию
            ResultNum = Square(Table, Result, N, Point / 100, Point % 100, BestNum, Current + 1); //если нашёлся результат лучше, чем наш
            if (ResultNum < BestNum) {//если там в конце нашёлся вариант лучше, то мы должны его запомнить
                BestNum = ResultNum;//присваиваем новый лучший результат
                Result[Current - 1][0] = x + 1;
                Result[Current - 1][1] = y + 1;
                Result[Current - 1][2] = i;
            }
        }
        else
        {//если нет,значит мы всё закрасили сравниваем с лучшим и делаем выход
            if (Current < BestNum)
            {
                Result[Current - 1][0] = x + 1;
                Result[Current - 1][1] = y + 1;
                Result[Current - 1][2] = i;
                BestNum = Current;//присваиваем новый лучший результат
            }
            Coloring(x, y, i, 0, Table);//чистим перед выходом всё что на данном этапе закрасили
            return BestNum;//возвращаем лучший результат
        }
    }
    Coloring(x, y, MaxSize, 0, Table);//чистим всё на данной итерации
    return BestNum;//возвращаем лучший результат
}

int FindBestSol(vector<vector<int> >& Table, vector<vector<int> >& Result, int N) {
    int Point = 0;
    int ResultNum = 0;
    int Zoom = 1;
    int BestNum = 0;
    //происходит маштабирование квадрата для ускорения
    if (N % 3 == 0)
    {
        Zoom = N / 3;
        N = 3;
    }
    if (N % 5 == 0)
    {
        Zoom = N / 5;
        N = 5;
    }
    //
    BestNum = 2 * N + 1;//любой квадрат можно разбить всегда на 2N квадратов
    //расставление трех квадратов для ускорения алгоритма
    Coloring(0, 0, (N - 1) / 2, 1, Table);//красим нужную часть квадрата
    Result[0][0] = 1;
    Result[0][1] = 1;
    Result[0][2] = (N - 1) / 2;
    Coloring(0, (N - 1) / 2, (N + 1) / 2, 2, Table);//красим нужную часть квадрата
    Result[1][0] = 1;
    Result[1][1] = (N + 1) / 2;
    Result[1][2] = (N + 1) / 2;
    Coloring((N + 1) / 2, (N + 1) / 2, (N - 1) / 2, 3, Table);//красим нужную часть квадрата
    Result[2][0] = (N + 1) / 2 + 1;
    Result[2][1] = (N + 1) / 2 + 1;
    Result[2][2] = (N - 1) / 2;
    //
    Point = SearchEmptyArea(0, N - 1, Table, N);//вызываем поиск точки
    //входим в рекурсию и ищем количество квадратов
    ResultNum = Square(Table, Result, N, Point / 100, Point % 100, BestNum, 4);
    //если нашёлся результат лучше, чем наш
    if (ResultNum < BestNum)
    {
        BestNum = ResultNum;//присваиваем новый лучший результат
    }
    //возврат к изначальным размерам квадрата в случае если происходило маштабирование
    if (Zoom>1)
        for (int i = 0; i < BestNum; i++)
        {
            Result[i][0] = (Result[i][0] - 1)*Zoom + 1;
            Result[i][1] = (Result[i][1] - 1)*Zoom + 1;
            Result[i][2] *= Zoom;
        }
    //
    return BestNum;
}

int main()
{
    //
    int N=0;
    cout << "enter size of square (2 to 40): ";
    cin >> N ;
    vector<vector<int>> Table(N,vector<int>(N,0));//Создаем двумерный массив с нулями
    vector<vector<int>> Result(2 * N,vector<int>(3,0));//Создаем массив для результатов
    cout << endl;
    //если длина стороны столешницы кратна 2, то самое минимальное разбиение на 4 части
    if ((N % 2) == 0)
    {
        cout << 4 << endl;//минимальное количество обрезков(квадратов)
        cout << 1 << " " << 1 << " " << N / 2 << endl;//левый верхний квадрат
        cout << 1 << " " << N / 2 + 1 << " " << N / 2 << endl;//левый нижний квадрат
        cout << N / 2 + 1 << " " << 1 << " " << N / 2 << endl;//правый верхний квадрат
        cout << N / 2 + 1 << " " << N / 2 + 1 << " " << N / 2 << endl;//правый нижний квадрат
    }
    else//если квадрат с нечётной стороной
    {
        int BestNum = FindBestSol(Table, Result, N);//вызываем функцию для поиска наилучшего решения
        cout << BestNum;//минимальное количество обрезков(квадратов)
        for (int i = 0; i < BestNum; i++)
        {
            cout << endl;
            for (int j = 0; j < 3; j++)
                cout << Result[i][j] << " ";
        }
    }
    //
    cout << endl;
    getchar();
    return 0;
}
