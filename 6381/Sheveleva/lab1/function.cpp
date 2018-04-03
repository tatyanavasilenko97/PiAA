// Функция удаляет последний элемент в массиве решений
void DeleteSquares (int **solution, int quantity_of_squares, int **box_of_squares)
{
	for (int i = solution[quantity_of_squares][0] - 1; 
		 i < solution[quantity_of_squares][0] + solution[quantity_of_squares][2] - 1;
		 i++)
		for (int j = solution[quantity_of_squares][1] - 1; 
			 j < solution[quantity_of_squares][1] + solution[quantity_of_squares][2] - 1; 
			 j++)
					box_of_squares[i][j] = 0;
	
	for (int i = 0; i < 3; i++)
		solution[quantity_of_squares][i] = 0;
}

// Функция создания элемента
void CreateSquares (int x, int y, int diagonal_of_squares, int **solution,
				    int quantity_of_squares, int **box_of_squares)
{
	solution[quantity_of_squares][0] = x;
	solution[quantity_of_squares][1] = y;
	solution[quantity_of_squares][2] = diagonal_of_squares;
	
	for (int i = x - 1; i < x + diagonal_of_squares - 1; i++)
		for (int j = y - 1; j < y + diagonal_of_squares - 1; j++)
			box_of_squares[i][j] = 1;
}

// Первое заполнение массива решений по оптимизации
void FirstSquares (int diagonal_of_squares, int diagonal_of_box, int **solution, int **box_of_squares)
{
	CreateSquares (1, 1, diagonal_of_squares, solution, 0, box_of_squares);
	CreateSquares (1, diagonal_of_squares + 1, diagonal_of_box - diagonal_of_squares, solution, 1, box_of_squares);
	CreateSquares (diagonal_of_squares + 1, 1, diagonal_of_box - diagonal_of_squares, solution, 2, box_of_squares);
}

// Поиск свободной клетки для заполнения
void SearchForPlaseForSquares (int &x, int &y, int diagonal_of_box, 
							   int **box_of_squares)
{
	for (int i = diagonal_of_box / 3; i < diagonal_of_box; i++)
		for (int j = diagonal_of_box / 3; j < diagonal_of_box; j++)
			if (box_of_squares[j][i] == 0)
				{					
					x = j + 1;
					y = i + 1;
					return;
				}
	x = 0;
	y = 0;
}

// Проверка возможности вставки квадрата с переданной диагональю
bool CellTest (int x, int y, int diagonal_of_squares,
			   int diagonal_of_box, int **box_of_squares)
{
	if ((x - 1 + diagonal_of_squares > diagonal_of_box) || (y - 1 + diagonal_of_squares > diagonal_of_box)) 
		return false;
	
	for (int i = x - 1; i < x + diagonal_of_squares - 1; i++)
		for (int j = y - 1; j < y + diagonal_of_squares - 1; j++)
			if (box_of_squares[i][j] == 1) return false; 	
	return true;
}

// Сохранение решения в ответ и возврат на одну позицию
void FoundSolution (int **solution, int **answer, int &quantity_of_squares, 
					int &min_quantity_of_squares, int **box_of_squares, int diagonal_of_box)
{
	quantity_of_squares--;
	for (int i = 0; i < diagonal_of_box + 4; i++)
		for (int j = 0; j < 3; j++)
			answer[i][j] = 0;
				
	for (int i = 0; i <= quantity_of_squares; i++)
		for (int j = 0; j < 3; j++)
			answer[i][j] = solution [i][j];
	min_quantity_of_squares = quantity_of_squares - 1;// Дабы было лишь первое найденное
	DeleteSquares (solution, quantity_of_squares, box_of_squares);
}
