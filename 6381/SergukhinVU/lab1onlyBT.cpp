#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

void removeSquare(int** &squareTmp, int color, int x, int y, int n); // Удаление квадрата определенного размера
bool putSquare(int** &squareTmp, int color, int size, int x, int y, int n); // Установка квадрата определенного размера
bool hasEmptySquare(int** &squareTmp, int& x, int& y, int n);  // Поиск незаполненной клетки
void backTracking(int& min_square_num, int n, int** &squareTmp, int** &squareBest, int x, int y); // Функция выполняющая заполения квадрата с использованием backtracking
int main() 
{
	int n;
	int length [40] = {0};
	int min_square_num = 40;
	cin >> n;
	

	int** squareTmp = new int*[n];
	int** squareBest = new int*[n];

	for (int i = 0; i < n; i++) // Заполняем уже уменьшенный согласно масштабу квадрат нулями
	{
		squareTmp[i] = new int[n];
		squareBest[i] = new int[n];
		for (int j = 0; j < n; j++) 
		{
			squareTmp[i][j] = 0;
			squareBest[i][j] = 0;
		}
	}
	

	//вызов рекурсивной функции	
		backTracking(min_square_num, n, squareTmp, squareBest, 0, 0);

	//вычисление длинны стороны каждого квадрата 
		cout << min_square_num << endl;
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				length[squareBest[i][j]]++;
		for (int i = 0; i<40; i++)
			length[i] = sqrt(length[i]);

	//печать квадрата с учетом его масштаба
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j<n; j++)
			{
				if (((i==0)&&(j==0))||
					((i==0)&&(squareBest[i][j-1]!=squareBest[i][j]))||
					((j==0)&&(squareBest[i-1][j]!=squareBest[i][j]))||
					((j!=0)&&(i!=0)&&(squareBest[i-1][j]!= squareBest[i][j])&&(squareBest[i][j-1] != squareBest[i][j])))
				{
						cout << (i+1) << " " << (j+1) << " " << length[squareBest[i][j]] << endl;
				}
			}
		}	
	
    return 0;
}

void removeSquare(int** &squareTmp, int color, int x, int y, int n) // Удаление квадрата определенного размера
 { 
	for (int i = y; (i < n) && (squareTmp[i][x] == color); i++)
	{
		for (int j = x; (j < n) && (squareTmp[i][j] == color); j++)
			squareTmp[i][j] = 0;
	}
}

bool putSquare(int** &squareTmp, int color, int size, int x, int y, int n)// Установка квадрата определенного размера
{ 

	if ((n < x + size) || (n < y + size))
		return false;
			
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (squareTmp[i+y][j+x] != 0 )
					return false;			
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			squareTmp[i + y][j + x] = color;
}

bool hasEmptySquare(int** &squareTmp, int& x, int& y, int n)  // Поиск незаполненной клетки
{
	while (y < n)
	 {
		while (x < n) 
		{
			if (squareTmp[y][x] == 0)
				return true;
			if (x == n - 1) 
			{
				y++;
				x = 0;
				break;
			}
			x++;
		}
	}
	return false;
}

void backTracking(int& min_square_num, int n, int** &squareTmp, int** &squareBest, int x, int y)  // Основная рекурсивная функция
{  
	static int temp_square = 1;
	if (temp_square >= min_square_num)
		return;

	for (int i = 1; i <= n-1; i++)
	 {
		if (putSquare(squareTmp, temp_square, i, x, y, n)) 
		{
			temp_square++;
			int x_1 = x;
			int y_1 = y;
			if (hasEmptySquare(squareTmp, x_1, y_1, n) )
				backTracking(min_square_num, n, squareTmp, squareBest, x_1, y_1);
			else 
			{
				temp_square--;
				if (temp_square < min_square_num) 
				{
					min_square_num  = temp_square;
					for (int i = 0; i < n; i++)
						for (int j = 0; j < n; j++)
							squareBest[i][j] = squareTmp[i][j];
				}
				removeSquare(squareTmp, temp_square, x, y, n);
				return;
			}
			temp_square--;
			removeSquare(squareTmp, temp_square, x, y, n);
		}
	}
}