#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

void removeSquare(int** &squareTmp, int color, int x, int y, int n); // Удаление квадрата определенного размера
bool putSquare(int** &squareTmp, int color, int size, int x, int y, int n); // Установка квадрата определенного размера
bool hasEmptySquare(int** &squareTmp, int& x, int& y, int n);  // Поиск незаполненной клетки
void backTracking(int& min_square_num, int n, int** &squareTmp, int** &squareBest, int x, int y, int& temp_square); // Функция выполняющая заполения квадрата с использованием backtracking



int main() 
{
	int input_size;
	int n;
	int scale; 
	int temp_square = 4;
	int length [40] = {0};
	int min_square_num = 40;
	cin >> input_size;

	if (input_size % 2 == 0)//ищем минимальный простой делитель числа, по которому програма определит число квадратов и их положение
		{
			n=2;
		}

	else if (input_size % 3 == 0)
		n = 3;

	else if (input_size % 5 == 0)
		n = 5;

	//Можно продолжить проверку со следущими простыми числами в порядки возрастания,
	//но в нашем случае, числа от 2 до 40, либо имеют наименьший простой делитель 2, 3, 5, либо сами являются простыми
	else
		n = input_size;
	
	scale = input_size/n; // масштаб

	if(n==2)//Вывод если четное
	{
		cout <<"4"<< endl;
		cout << 1   << " "  << 1   << " " << scale << endl;
		cout << scale+1 << " "  << 1   << " " << scale << endl;
		cout << 1   << " "  << scale+1 << " " << scale << endl;
		cout << scale+1 << " "  << scale+1 << " " << scale << endl;


		return 0;
	}

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
	
	//оптимизация в виде изнвачального расположения трёх квадратов 
		
		putSquare(squareTmp, 1, (n + 1) / 2, 0, 0, n);
		putSquare(squareTmp, 2, (n - 1) / 2, (n + 1) / 2, 0, n);
		putSquare(squareTmp, 3, (n - 1) / 2, 0, (n + 1) / 2, n);



	//вызов рекурсивной функции	
		backTracking(min_square_num, n, squareTmp, squareBest, (n+1) / 2, (n-1) / 2, temp_square);

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
						cout << (scale*i)+1 << " " << (scale*j)+1<< " " << scale*length[squareBest[i][j]] << endl;
					

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

void backTracking(int& min_square_num, int n, int** &squareTmp, int** &squareBest, int x, int y, int& temp_square)  // Основная рекурсивная функция
{  
	if (temp_square >= min_square_num)
		return;

	for (int i = 1; i <= (n+1)/2; i++)
	 {
		if (putSquare(squareTmp, temp_square, i, x, y, n)) 
		{
			temp_square++;
			int x_1 = x;
			int y_1 = y;
			if (hasEmptySquare(squareTmp, x_1, y_1, n) )
				backTracking(min_square_num, n, squareTmp, squareBest, x_1, y_1, temp_square);
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