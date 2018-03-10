#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

void ColoringSquare(int x, int y, int size, int colour, vector<vector<int> >& Table) {//красим нужным цветом области квадрата
	for (int i = x; i < x + size; i++)
		for (int j = y; j < y + size; j++)
			Table[i][j] = colour;
}

int SearchEmptyArea(int last_x, int last_y, vector<vector<int> > & Table, int N) {
	for (int j = last_y; j < N; j++) {
		if (Table[last_x][j] == 0)
			return last_x * 100 + j;
	}
	for (int i = last_x + 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Table[i][j] == 0)
				return i * 100 + j;
		}
	}
	return -1;//если пустых больше нет
}

int Accommodation(vector<vector<int> > & Table, vector<vector<int> > & Result, int N, int x, int y, int BestNumber, int CurrentSquare) {
	int Point = 0;
	int MaxSize = N - 1;//максимальная сторона квадрата
	int ResultNumber = 0;
	int y1 = y + 1;

	if (CurrentSquare > BestNumber)//если количество квадратов больше лучшего предыдущего результата, то дальше смотреть нет смысла
		return BestNumber;

	while ((y1 < N) && (y1 >= 0)) {//проверка на пересечение справа
		if (Table[x][y1] != 0) {//если будет перекрытие квадратов
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
		ColoringSquare(x, y, i, CurrentSquare, Table);//красим нужную часть квадрата
		Point = SearchEmptyArea(x, y + i - 1, Table, N);//вызываем поиск точки
		if (Point >= 0) {//если точка есть, то рекурсивно вызываем новую функцию
			ResultNumber = Accommodation(Table, Result, N, Point / 100, Point % 100, BestNumber, CurrentSquare + 1); //если нашёлся результат лучше, чем наш
			if (ResultNumber < BestNumber) {//если там в конце нашёлся вариант лучше, то мы должны его запомнить
				BestNumber = ResultNumber;//присваиваем новый лучший результат
				Result[CurrentSquare - 1][0] = x + 1;
				Result[CurrentSquare - 1][1] = y + 1;
				Result[CurrentSquare - 1][2] = i;
			}
		}
		else {//если нет,значит мы всё закрасили сравниваем с лучшим и делаем выход
			if (CurrentSquare < BestNumber) {
				Result[CurrentSquare - 1][0] = x + 1;
				Result[CurrentSquare - 1][1] = y + 1;
				Result[CurrentSquare - 1][2] = i;
				BestNumber = CurrentSquare;//присваиваем новый лучший результат
			}
			ColoringSquare(x, y, i, 0, Table);//чистим перед выходом всё что на данном этапе закрасили
			return BestNumber;//возвращаем лучший результат
		}
	}
	ColoringSquare(x, y, MaxSize, 0, Table);//чистим всё на данной итерации
	return BestNumber;//возвращаем лучший результат
}

int FindBestSolution(vector<vector<int> >& Table, vector<vector<int> >& Result, int N) {
	int Point = 0;
	int ResultNumber = 0;
	int Zoom = 1;
	int BestNumber = 0;

	if (N % 3 == 0) {
		Zoom = N / 3;
		N = 3;
	}

	if (N % 5 == 0) {
		Zoom = N / 5;
		N = 5;
	}

	BestNumber = 2 * N + 1;//любой квадрат можно разбить всегда на 2N квадратов

	ColoringSquare(0, 0, (N - 1) / 2, 1, Table);//красим нужную часть квадрата
	Result[0][0] = 1;
	Result[0][1] = 1;
	Result[0][2] = (N - 1) / 2;
	ColoringSquare(0, (N - 1) / 2, (N + 1) / 2, 2, Table);//красим нужную часть квадрата
	Result[1][0] = 1;
	Result[1][1] = (N + 1) / 2;
	Result[1][2] = (N + 1) / 2;
	ColoringSquare((N + 1) / 2, (N + 1) / 2, (N - 1) / 2, 3, Table);//красим нужную часть квадрата
	Result[2][0] = (N + 1) / 2 + 1;
	Result[2][1] = (N + 1) / 2 + 1;
	Result[2][2] = (N - 1) / 2;
	Point = SearchEmptyArea(0, N - 1, Table, N);//вызываем поиск точки
	ResultNumber = Accommodation(Table, Result, N, Point / 100, Point % 100, BestNumber, 4); //если нашёлся результат лучше, чем наш
	if (ResultNumber < BestNumber) {
		BestNumber = ResultNumber;//присваиваем новый лучший результат
	}

	if (Zoom>1)
		for (int i = 0; i < BestNumber; i++)
		{
			Result[i][0] = (Result[i][0] - 1)*Zoom + 1;
			Result[i][1] = (Result[i][1] - 1)*Zoom + 1;
			Result[i][2] *= Zoom;
		}
	return BestNumber;
}

int main()
{
	int N = 0;
	cout << "Enter N (1<N<41): ";
	cin >> N;
	cout << endl;
	vector<vector<int> > Table(N, vector<int>(N, 0)); // Инициализировали массив NxN нулями
	vector<vector<int> > Result(2 * N, vector<int>(3, 0));
	if ((N % 2) == 0) //если длина стороны столешницы кратна 2, то самое минимальное разбиение на 4 части
	{
		cout << 4 << endl;//минимальное количество обрезков(квадратов)
		cout << 1 << " " << 1 << " " << N / 2 << endl;//левый верхний квадрат
		cout << 1 << " " << N / 2 + 1 << " " << N / 2 << endl;//левый нижний квадрат
		cout << N / 2 + 1 << " " << 1 << " " << N / 2 << endl;//правый верхний квадрат
		cout << N / 2 + 1 << " " << N / 2 + 1 << " " << N / 2 << endl;//правый нижний квадрат
	}
	else//если квадрат с нечётной стороной
	{
		int BestNumber = FindBestSolution(Table, Result, N);//вызываем функцию для поиска наилучшего решения
		cout << BestNumber;//минимальное количество обрезков(квадратов)
		for (int i = 0; i < BestNumber; i++)
		{
			cout << endl;
			for (int j = 0; j < 3; j++)
				cout << Result[i][j] << " ";
		}
	}
	getch();
	return 0;
}