#include <iostream>  
#include <cstring>
#define N_MAX 17				// максимальное количество квадратов, на которе мы можем разбить наш квадрат
								// при n <= 40 не превосходит 15 (http://www2.stetson.edu/~efriedma/mathmagic/1298.html)
#define NUMBER_OF_PRIME 8		// количество простых чисел в [10;40]		
#define MAX_SIDE_LENGTH 40		// максимальная длина квадрата
#define MAX_AREA 1600			// максимальная площадь квадрата			
class Square
{
public:
	int x;
	int y;
	int size;
};

class Point
{
public: 
	int x;
	int y;
};

class Result
{
public:
	// матрица: 1 столбец - простая площадь, 2-ой - количество квадратов, затем идут площадиквадратов, на которые разбиваем 
	const int matrix_of_squares_for_primes[NUMBER_OF_PRIME][N_MAX] =
	{
		{ 11, 11, 6, 5, 5, 4, 2, 2, 2, 2, 1, 1, 1 },
		{ 13, 11, 7, 6, 6, 4, 3, 3, 2, 2, 2, 1, 1 },
		{ 17, 12, 9, 8, 8, 5, 4, 4, 3, 2, 2, 2, 1, 1 },
		{ 19, 13, 10, 9, 9, 5, 5, 5, 3, 2, 2, 2, 1, 1, 1 },
		{ 23, 13, 12, 11, 11, 7, 5, 5, 4, 3, 3, 2, 2, 1, 1 },
		{ 29, 14, 17, 12, 12, 9, 8, 8, 4, 4, 3, 2, 2, 2, 1, 1 },
		{ 31, 15, 16, 15, 15, 8, 8, 8, 4, 4, 4, 2, 2, 2, 1, 1, 1 },
		{ 37, 15, 19, 18, 18, 11, 8, 8, 6, 5, 5, 3, 3, 2, 1, 1, 1 },
	};
	Square squares[N_MAX];
	Square best[N_MAX];
	int resultSquare[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH];		// в этот квадрат склеиваем
	int resultBest[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH];	    // лучший результат
//	Result() : squares(new Square[N_MAX]), best(new Square[N_MAX]) {}
//	~Result() { delete[] squares, delete[] best;}
};

// поиск количества левых верхних координат пустой области
int find(int size, Point points[MAX_AREA], int my_n, Result res)
{
	int num_of_points = 0;								// количество найденных координат
	for (int y = 0; y <= (my_n - size); y++)
		for (int x = 0; x <= (my_n - size); x++)
			if (res.resultSquare[y][x] == 0)				// нашли пустую точку
			{
				bool is_empty = true;
				for (int i = y; i < (y + size); i++)	// проверка: есть ли в этой точке пустой квадрат
				{
					for (int j = x; j < (x + size); j++)
						if (res.resultSquare[i][j] != 0)
						{
							is_empty = false;
							break;
						}
					if (!is_empty)
						break;
				}
				if (is_empty)								// если пусто, в массив точек записываем 
				{											// координаты (x,y)
					points[num_of_points].x = x;
					points[num_of_points].y = y;
					num_of_points++;						// и увеличиваем количество найденных координат
				}
			}
	return num_of_points;
}

// вывод координаты верхнего левого угла каждого квадрата
void print(Square s[N_MAX], int num_of_squares)
{
 	std::cout << num_of_squares << std::endl;
	for (int i = 0; i < num_of_squares; i++)
		std::cout << s[i].x << " " << s[i].y << " " << s[i].size << std::endl;
}

void backtracking(int blocks[], int num_of_current, 
	int yeah, bool show, int my_n, bool &finish, Result res)
{
	// если столешница построена то все ок
	if (num_of_current == yeah)
	{
		memcpy(res.resultBest, res.resultSquare, sizeof(res.resultSquare));
		if (show)
			print(res.squares, num_of_current);
		else
			memcpy(res.best, res.squares, sizeof(res.squares));
		finish = true;
	}

	else
	{
		int npoints;				// пишем количество найденных координат
		Point points[MAX_AREA];
		if ((npoints = find(blocks[num_of_current], points, my_n, res)) == 0)	// если не найдены, то все
			return;
		for (int i = 0; i < npoints; i++)			// ищем по одному
		{
			int x = points[i].x;
			int y = points[i].y;
			int s = blocks[num_of_current];
			if (num_of_current == 0 && (y != 0 || x != 0))	// первый лист в левом верхнем углу
				continue;
			if (num_of_current == 1 && (y != 0 || x != blocks[0]))	// второй в верхний правый угол
				continue;
			if (num_of_current == 2 && (y != blocks[0] || x != 0))	// третий в левый нижний угол
				continue;
			if (num_of_current == 3 && x != (my_n - blocks[num_of_current]))	// четвертый к правому краю
				continue;
			if (num_of_current == 4 && (x != (my_n - blocks[num_of_current]) &&
				y != (my_n- blocks[num_of_current])))								// пятый или с правым или с нижним краем
				continue;
			res.squares[num_of_current].x = (x + 1);
			res.squares[num_of_current].y = (y + 1);
			res.squares[num_of_current].size = s;
			for (int iy = y; iy < (y + s); iy++)					// отмечаем квадратик, который будет заполнен
				for (int ix = x; ix < (x + s); ix++)
					res.resultSquare[iy][ix] = s;					
			backtracking(blocks, num_of_current + 1, yeah,			// идем рекурсивно
				show, my_n, finish, res);
			if (finish)												
				return;												// что-то пошло не так, обнуляем квадрат
			for (int iy = y; iy < (y + s); iy++)
				for (int ix = x; ix < (x + s); ix++)
					res.resultSquare[iy][ix] = 0;
		}
	}
}

// ищем минимальное количество квадратиков
void solve(int my_n, bool &finish, Result res)
{
	int resolution[N_MAX];
	int num_of_resolution;
	for (int i = 0; i != NUMBER_OF_PRIME; i++)
		if (res.matrix_of_squares_for_primes[i][0] == my_n)
		{
			// задаем начальные данные, общее количество квадратиков, схему разделения
			num_of_resolution = res.matrix_of_squares_for_primes[i][1];
			for (int j = 0; j < num_of_resolution; j++)
				resolution[j] = res.matrix_of_squares_for_primes[i][j + 2];
			break;
		}
	finish = false;
	//очищаем большой квадрат
	memset(res.resultSquare, 0, sizeof(res.resultSquare));
	// запускаем раделение квадрата по лучшей схеме
	backtracking(resolution, 0, num_of_resolution, true, my_n, finish, res);
}

void out_X_Y_size(int x, int y, int size)
{
	std::cout << x << " " << y << " " << size << std::endl;
}

void out_by_n_mod_2(int size, int answer)
{
	// при четном n все выводим напрямую
	std::cout << answer << std::endl;
	out_X_Y_size(1, 1, size);
	out_X_Y_size(1, 1 + size, size);
	out_X_Y_size(1 + size, 1, size);
	out_X_Y_size(1 + size, 1 + size, size);
}

void out_by_n_mod_6(int size, int answer)
{
	// так же и для n= 6k+3
	std::cout << answer << std::endl;
	out_X_Y_size(1, 1, size * 2);
	out_X_Y_size(1 + size * 2, 1, size);
	out_X_Y_size(1 + size * 2, 1 + size, size);
	out_X_Y_size(1 + size * 2, 1 + size * 2, size);
	out_X_Y_size(1, 1 + size * 2, size);
	out_X_Y_size(1 + size, 1 + size * 2, size);
}

void out_by_n_mod_5(int size, int answer)
{
	std::cout << answer << std::endl;
	out_X_Y_size(1, 1, size * 3);
	out_X_Y_size(1 + size * 3, 1, size * 2);
	out_X_Y_size(1 + size * 3, 1 + size * 2, size * 2);
	out_X_Y_size(1, 1 + size * 3, size * 2);
	out_X_Y_size(1 + size * 2, 1 + size * 3, size);
	out_X_Y_size(1 + size * 2, 1 + size * 4, size);
	out_X_Y_size(1 + size * 3, 1 + size * 4, size);
	out_X_Y_size(1 + size * 4, 1 + size * 4, size);
}

void out_by_n_mod_7(int size, int answer)
{
	std::cout << answer << std::endl;
	out_X_Y_size(1, 1, size * 4);
	out_X_Y_size(1 + size * 4, 1, size * 3);
	out_X_Y_size(1, 1 + size * 4, size * 3);
	out_X_Y_size(1 + size * 3, 1 + size * 5, size * 2);
	out_X_Y_size(1 + size * 5, 1 + size * 5, size * 2);
	out_X_Y_size(1 + size * 5, 1 + size * 3, size * 2);
	out_X_Y_size(1 + size * 4, 1 + size * 3, size);
	out_X_Y_size(1 + size * 4, 1 + size * 4, size);
	out_X_Y_size(1 + size * 3, 1 + size * 4, size);
}

int main()
{
	Result res;
	bool finish = false;
	int my_n;									// длина квадрата, указываемая пользователем
	int array_of_answers[] = { 4, 6, 8, 9 };	// количества квадратов для известных случаев
	std::cin >> my_n;
	int size = 0;
	if (my_n % 2 == 0)
	{
		out_by_n_mod_2(my_n / 2, array_of_answers[0]);
	}
	else if (my_n % 6 == 3)
	{
		out_by_n_mod_6(my_n / 3, array_of_answers[1]);
	}
	else if (my_n % 5 == 0)
	{
		out_by_n_mod_5(my_n / 5, array_of_answers[2]);
	}
	else if (my_n % 7 == 0)
	{
		out_by_n_mod_7(my_n / 7, array_of_answers[3]);
	}
	else
		solve(my_n, finish, res);
	return 0;
}
