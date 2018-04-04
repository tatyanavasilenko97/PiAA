#include <iostream>
#include "function.h"

using namespace std ;

int main () 
{
	int diagonal_of_box = 0; // Длина стороны поступающего квадрата
	int **solution = nullptr, // Массив решений
		**answer = nullptr, // Массив ответа
		**box_of_squares = nullptr; // Массив с элементами квадрата
	int min_quantity_of_squares = 0; // минимальное количество квадратов
	int max_diagonal_of_squares = 0; // максимальная диагональ первого квадрата
	int our_first_divisor = 1; // Первый делитель стороны квадрата
	int x = 1, y = 1; // координаты квадрата
	
	int prime_numbers[] {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
						 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
		
	cout << "Введите диагональ квадрата: ";
	cin >> diagonal_of_box;
	cout << "Решение: " << endl;
	
	// Создание и обнуление динамических массивов	
	box_of_squares = new int*[diagonal_of_box]; 
    for (int i = 0; i < diagonal_of_box; i++) {
        box_of_squares[i] = new int[diagonal_of_box];
        for (int j = 0; j < diagonal_of_box; j++)
			box_of_squares[i][j] = 0;
	     }
	solution = new int*[diagonal_of_box + 4]; 
    for (int i = 0; i < diagonal_of_box + 4; i++)
        solution[i] = new int[3];
    
    answer = new int*[diagonal_of_box + 4]; 
    for (int i = 0; i < diagonal_of_box + 4; i++)
        answer[i] = new int[3];      
    
    // Решение для квадрата стороной кратности 2
    if (diagonal_of_box % 2 == 0) 
    {
		cout << 4 << endl;
		cout << "1 1 "<<diagonal_of_box / 2 << endl;
		cout << "1 " << diagonal_of_box / 2 + 1<< ' '<<diagonal_of_box / 2 << endl;
		cout << diagonal_of_box / 2 + 1<<" 1 " <<  diagonal_of_box / 2 << endl;
		cout << diagonal_of_box / 2 + 1 <<' ' << diagonal_of_box / 2 + 1<< ' '<<diagonal_of_box / 2 << endl;
	}
    
    // Решение для остальных
    if (diagonal_of_box % 2 != 0) 
    {
		for (int i = 0; i < 24; i++) // Поиск первого делителя, 24 - размер массива простых чисел
			if (diagonal_of_box % prime_numbers[i] == 0)
			{
				our_first_divisor = prime_numbers[i];
				break;
			}
		
		// определяем максимальную диагональ первого квадрата
		if (our_first_divisor == 1) max_diagonal_of_squares = diagonal_of_box / 2 + 1;
		else max_diagonal_of_squares = diagonal_of_box / our_first_divisor * (our_first_divisor / 2 + 1);
		
		FirstSquares (max_diagonal_of_squares, diagonal_of_box, solution, box_of_squares);
		
		// Определяем максимально возможное минимальное количество квадратов
		if ((diagonal_of_box % 3 == 0) || (diagonal_of_box % 5 == 0))
			if (diagonal_of_box % 3 == 0) min_quantity_of_squares = 6;
			else min_quantity_of_squares = 8;
		else min_quantity_of_squares = diagonal_of_box + 2;
		
		x = max_diagonal_of_squares + 1;
		y = diagonal_of_box - diagonal_of_box / our_first_divisor * (our_first_divisor / 2 + 1) + 1;
		
		MinQuantityOfSquares (x, y, diagonal_of_box, max_diagonal_of_squares, solution, answer,
							  3,  min_quantity_of_squares, box_of_squares);   // 3 - это количество уже имеющихся квадратов
		
		cout << min_quantity_of_squares + 2 << endl;
		for (int i = 0; i < min_quantity_of_squares + 2; i++)
			cout << answer[i][0] << ' ' << answer[i][1] << ' ' << answer[i][2] << endl;
	}	
	
	// Освобождение памяти
	delete [] box_of_squares;
	delete [] answer;
	delete [] solution;      
	                                                                                                                                                                                                                                                                                                                                                                                              
	return 0;
}
