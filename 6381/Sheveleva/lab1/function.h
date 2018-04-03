// Функция удаляет последний элемент в массиве решений
void DeleteSquares (int **solution, int quantity_of_squares, int **box_of_squares);

// Функция создания элемента
void CreateSquares (int x, int y, int diagonal_of_squares, int **solution,
				    int quantity_of_squares, int **box_of_squares);

// Первое заполнение массива решений по оптимизации
void FirstSquares (int diagonal_of_squares, int diagonal_of_box, int **solution, int **box_of_squares);

// Поиск свободной клетки для заполнения
void SearchForPlaseForSquares (int &x, int &y, int diagonal_of_box, 
							   int **box_of_squares);

// Проверка возможности вставки квадрата с переданной диагональю
bool CellTest (int x, int y, int diagonal_of_squares,
			   int diagonal_of_box, int **box_of_squares);

// Сохранение решения в ответ и возврат на одну позицию
void FoundSolution (int **solution, int **answer, int &quantity_of_squares, 
					int &min_quantity_of_squares, int **box_of_squares, int diagonal_of_box);
// Заполнение квадрата
void MinQuantityOfSquares (int x, int y, int diagonal_of_box, int max_diagonal_of_squares, int **solution, 
						   int **answer, int quantity_of_squares, int &min_quantity_of_squares, int **box_of_squares);
