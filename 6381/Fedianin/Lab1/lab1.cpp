#include <iostream>
#include <vector>

using namespace std;

bool Primes(int n); // Проверка числа на простоту и делимость на 2, 3, 5 
void NoSimpleSquares(vector<vector<int>>& TempTable, int size); // Функция для квадратов с не простой стороной, делящейся на 2, 3, 5
void SimpleSquares(vector<vector<int>>& TempTable, int size, vector<vector<int>>& BestTable); // Функция для квадратов с простой стороной, не делящейся на 2, 3, 5
void Print_x_y_size_of_a_square(int x, int y, int size); // Вывести х, у, size квадрата
bool ArrangementSquares(vector<vector<int>>& Table, int N, int x, int y, int scale, int number); // Расстановка квадратов
bool go_beyond_the_table(int x, int y, int scale, int N); // Проверка на выход за пределы массива
void RemoveSquare(vector<vector<int>>& Table, int N, int x, int y, int number); // Удаление квадратов
bool FindFreeCell(vector<vector<int>>& Table, int N, int& x, int& y); // Поиск свободных клеток
int Alignment(vector<vector<int>>& Table, int N, int x, int y, vector<vector<int>>& bestTable); // Растановка квадратов
int FindSquare(vector<vector<int>>& Table, int N, int& x, int& y, int K); // Возвращает размер квадрата
void Print_x_y_size_of_a_table(vector<vector<int>>& Table, int N, int partNmbr); // Вывести координаты и размер всех квадратов
void PrintSquare(vector<vector<int>>& TempTable); // Вывести весь квадрат

int main(){
	int n;
	cout << "Enter the size of the table N (2<=N<=40)" << endl;
	cin >> n;
	vector<vector<int>> TempTable(n, vector <int> (n));
	vector<vector<int>> BestTable(n, vector <int> (n));

	if (Primes(n)) SimpleSquares(TempTable, n, BestTable);
	else NoSimpleSquares(TempTable, n);
	
	return 0;
}

bool Primes(int n){
	vector<int> primes = {7, 11, 13, 17, 19, 23, 29, 31, 37};//массив простых чисел, не делящихся на 2, 3, 5
	for (int i = 0; i < primes.size(); i++){
		if (n == primes[i]) return true;	
	}
	return false;
}

void Print_x_y_size_of_a_square(int x, int y, int size) {
	cout << y + 1 << " " << x + 1 << " " << size << endl;
}

void NoSimpleSquares(vector<vector<int>>& TempTable, int size){
	cout << "No Simple Square" << endl;
	if (size % 2 == 0){
		cout << 4 << endl;
		// для таблицы
		cout << "Table" << endl;		
		Print_x_y_size_of_a_square(0, 0, size / 2);
		Print_x_y_size_of_a_square(0, size / 2, size / 2);
		Print_x_y_size_of_a_square(size / 2, 0, size / 2);
		Print_x_y_size_of_a_square(size / 2, size / 2, size / 2);
		
		// для вывода всего квадрата
		ArrangementSquares(TempTable, size, 0, 0, size / 2, 1);
		ArrangementSquares(TempTable, size, 0, size / 2, size / 2, 2);
		ArrangementSquares(TempTable, size, size / 2, 0, size / 2, 3);
		ArrangementSquares(TempTable, size, size / 2, size / 2, size / 2, 4);

	} 
	else if (size % 3 == 0) {
		cout << 6 << endl;
		cout << "Table" << endl;
		Print_x_y_size_of_a_square(0, 0, size * 2/3);
		Print_x_y_size_of_a_square(size * 2/3, 0, size / 3);
		Print_x_y_size_of_a_square(size * 2/3, size / 3, size / 3);
		Print_x_y_size_of_a_square(size * 2/3, size * 2/3, size / 3);
		Print_x_y_size_of_a_square(0, size * 2/3, size / 3);
		Print_x_y_size_of_a_square(size / 3, size * 2/3, size / 3);
		
		ArrangementSquares(TempTable, size, 0, 0, size * 2/3, 1);
		ArrangementSquares(TempTable, size, size * 2/3, 0, size / 3, 2);
		ArrangementSquares(TempTable, size, size * 2/3, size / 3, size / 3, 3);
		ArrangementSquares(TempTable, size, size * 2/3, size * 2/3, size / 3, 4);
		ArrangementSquares(TempTable, size, 0, size * 2/3, size / 3, 5);
		ArrangementSquares(TempTable, size, size / 3, size * 2/3, size / 3, 6);
	}
	else if (size % 5 == 0) {
		cout << 8 << endl;
		cout << "Table" << endl;
		Print_x_y_size_of_a_square(0, 0, size * 3/5);
		Print_x_y_size_of_a_square(size * 3/5, 0, size * 2/5);
		Print_x_y_size_of_a_square(size * 3/5, size * 2/5, size * 2/5);
		Print_x_y_size_of_a_square(0, size * 3/5, size * 2/5);
		Print_x_y_size_of_a_square(size * 2/5, size * 3/5, size/5);
		Print_x_y_size_of_a_square(size * 2/5, size * 4/5, size/5);
		Print_x_y_size_of_a_square(size * 3/5, size * 4/5, size/5);
		Print_x_y_size_of_a_square(size * 4/5, size * 4/5, size/5);
		
		ArrangementSquares(TempTable, size, 0, 0, size * 3/5, 1);
		ArrangementSquares(TempTable, size, size * 3/5, 0, size * 2/5, 2);
		ArrangementSquares(TempTable, size, size * 3/5, size * 2/5, size * 2/5, 3);
		ArrangementSquares(TempTable, size, 0, size * 3/5, size * 2/5, 4);
		ArrangementSquares(TempTable, size, size * 2/5, size * 3/5, size/5, 5);
		ArrangementSquares(TempTable, size, size * 2/5, size * 4/5, size/5, 6);
		ArrangementSquares(TempTable, size, size * 3/5, size * 4/5, size/5, 7);
		ArrangementSquares(TempTable, size, size * 4/5, size * 4/5, size/5, 8);
	} 
	else {
		cout << "Error in function NoSimpleSquares" << endl;
	}
	cout << "Square" << endl;
	PrintSquare(TempTable);
}

void SimpleSquares(vector<vector<int>>& TempTable, int size, vector<vector<int>>& BestTable){
	cout << "Simple Square" << endl;
	//Растановка известных квадратов
	ArrangementSquares(TempTable, size, 0, 0, (size + 1) / 2, 1);
    ArrangementSquares(TempTable, size, (size + 1) / 2, 0, size / 2, 2);
    ArrangementSquares(TempTable, size, 0, (size + 1) / 2, size / 2, 3);
    int K = Alignment(TempTable, size, (size / 2) + 1, size / 2, BestTable);
	cout << K << endl;
	cout << "Table" << endl;	
    Print_x_y_size_of_a_table(BestTable, size, K);
	cout << "Square" << endl;
	PrintSquare(BestTable);
}

bool ArrangementSquares(vector<vector<int>>& TempTable, int size, int x, int y, int scale, int number){
	if (go_beyond_the_table(x, y, scale, size)) {
		//cout << "Going out of the array" << endl;
		return false;
	}
    for(int i = 0; i < scale; ++i) {
        for (int j = 0; j < scale; ++j) {
            if (!TempTable[y+i][x+j]) //если равен 0
                TempTable[y+i][x+j] = number;
            else
            {
                RemoveSquare(TempTable, size, x, y, number);
				//cout << "Remove square" << endl;
                return false;
            }
        }
    }
    return true;
}	

bool go_beyond_the_table(int x, int y, int scale, int size) {
    return ((scale > (size - x)) || (scale > (size - y)));
}	
	
void RemoveSquare(vector<vector<int>>& TempTable, int size, int x, int y, int number)
{
    for(int i = y; (i < size) && (TempTable[i][x] == number); ++i){
        for (int j = x; (j < size) && (TempTable[i][j] == number); ++j) TempTable[i][j] = 0;
    }
}	

bool FindFreeCell(vector<vector<int>>& TempTable, int size, int& x, int& y)
{
    while (TempTable[y][x] != 0)
    {
        if (x == size - 1)
        {
            x = 0;
            ++y;
        }
        else ++x;
        if (x >= size || y >= size)
            return false;
    }
    return true;
}

int Alignment(vector<vector<int>>& TempTable, int size, int x, int y, vector<vector<int>>& BestTable)
{
    static int CounterSquares = 4; // 3 квадрата уже поставили
    static int BestCounterSquares = 40; // макс. число квадратов для стола N = 40

    if (CounterSquares > BestCounterSquares) return 0;
    if (FindFreeCell(TempTable, size, x, y)) // Если есть свободная клетка
    {
        for (int i = size - 1; i > 0; --i)
        {
            if (ArrangementSquares(TempTable, size, x, y, i, CounterSquares)) // Ставим квадрат с номером 4
            {
                ++CounterSquares;
                Alignment(TempTable, size, x, y, BestTable); // Вызываем рекурсию
                --CounterSquares;
            }
            RemoveSquare(TempTable, size, x, y, CounterSquares); // Удаляем квадрат
        }
    }
    else if ((CounterSquares - 1) < BestCounterSquares)
    {
        BestCounterSquares = CounterSquares - 1;
        BestTable = TempTable;
    }
    return BestCounterSquares;
}

void Print_x_y_size_of_a_table(vector<vector<int>>& TempTable, int size, int CounterSquares)
{
    int x, y, N;
    for(int i = 1; i <= CounterSquares; ++i)
    {
        x = 0;
        y = 0;
        N = FindSquare(TempTable, size, x, y, i);
		Print_x_y_size_of_a_square(x, y, N);
    }
}

int FindSquare(vector<vector<int>>& TempTable, int size, int& x, int& y, int i)
{
    while (TempTable[y][x] != i)
    {
        if (x == size - 1)
        {
            x = 0;
            ++y;
        }
        else ++x;
        if (x >= size || y >= size)
            return false;
    }
    int j = 0;
    while (TempTable[y][x+j] == i)
    {
        if ((x + j) < size) ++j;
        else return --j;
    }
    return j;
}

void PrintSquare(vector<vector<int>>& TempTable){
	for(int i = (TempTable.size() - 1); i >= 0; --i){
			for(int j = 0; j < TempTable.size(); ++j){
				cout << TempTable[i][j];
				if ((TempTable[i][j] >= 10) && (TempTable[i][j] <= 99)) cout << ' ';
				else cout << "  ";				
			}
			cout << endl << endl;
		}
	cout << endl;
}





















