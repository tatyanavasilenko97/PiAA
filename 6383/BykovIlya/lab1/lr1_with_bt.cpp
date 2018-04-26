#include <iostream>
#include <vector>
#include <cstring>

struct point
{
    int x;
    int y;
    bool isNotEmpty;
    point() : x(0), y(0), isNotEmpty(false) {}
};

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

point findEmptySquare(int x, int y, std::vector<std::vector<int> > & square, int n)
{
    point p;
    for (int j = y; j < n; j++)
    {
        if (square[x][j] == 0)
        {
            p.x = x; p.y = j; p.isNotEmpty = true;
            return p;
        }
	}
	for (int i = x + 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (square[i][j] == 0)
            {
                p.x = i; p.y = j; p.isNotEmpty = true;
                return p;
            }
		}
	}
	p.isNotEmpty = false;
	return p;
}

bool setSquare(int n, int x, int y, int size, int length, std::vector<std::vector<int> > & square)
{
	if (y + size > n || x + size > n)
    {
		return false;
	}
	for (int i = x; i < x + size; i++)
	{
		for (int j = y; j < y + size; j++)
		{
			if (square[i][j] = 0)
				return false;
		}
	}
	for (int i = x; i < x + size; i++)
	{
		for (int j = y; j < y + size; j++)
		{
			square[i][j] = length;
		}
	}
	return true;
}

int backtracking(std::vector<std::vector<int> > & square, std::vector<std::vector<int> > & bestSquare,
                 int n, int x, int y, int minNumSquare, int curNumSquare)
{
	point p;
	int maxSquare = n - 1;
	int resNum = 0;
	int _y = y + 1;
	if (curNumSquare > minNumSquare)
		return minNumSquare;
	while ((_y >= 0) && (_y < n))
    {
		if (square[x][_y] != 0)
		{
			maxSquare = _y - y;
			break;
		}
		_y++;
	}
	if (_y == n)
		maxSquare = n - y;
	if ((n - x) < maxSquare)
		maxSquare = n - x;

	for (int i = 1; i <= maxSquare; i++)
	{
		setSquare(n, x, y, i, curNumSquare, square);
		p = findEmptySquare(x, y + i - 1, square, n);
		if (p.isNotEmpty)
        {
			resNum = backtracking(square, bestSquare, n, p.x, p.y, minNumSquare, curNumSquare + 1);
			if (resNum < minNumSquare)
			{
				minNumSquare = resNum;
				bestSquare[curNumSquare - 1][0] = x + 1;
				bestSquare[curNumSquare - 1][1] = y + 1;
				bestSquare[curNumSquare - 1][2] = i;
			}
		}
		else
		{
			if (curNumSquare < minNumSquare)
			{
				bestSquare[curNumSquare - 1][0] = x + 1;
				bestSquare[curNumSquare - 1][1] = y + 1;
				bestSquare[curNumSquare - 1][2] = i;
				minNumSquare = curNumSquare;
			}
			setSquare(n, x, y, i, 0, square);
			return minNumSquare;
		}
	}
	setSquare(n, x, y, maxSquare, 0, square);
	return minNumSquare;
}

int main()
{
	int my_n;									// длина квадрата, указываемая пользователем
	int array_of_answers[] = { 4, 6, 8, 9 };	// количества квадратов для известных случаев
	std::cin >> my_n;
	std::vector<std::vector<int> > square(my_n, std::vector<int>(my_n, 0));
	std::vector<std::vector<int> > bestSquare(2 * my_n, std::vector<int>(3, 0));
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
    {
        point p;
		int minNumSquare = 0;
		int m = (my_n - 1) / 2;
		int k = (my_n + 1) / 2;
		setSquare(my_n, 0, 0, m, 1, square);
		bestSquare[0][0] = 1;
		bestSquare[0][1] = 1;
		bestSquare[0][2] = m;
		setSquare(my_n, 0, m, k, 2, square);
		bestSquare[1][0] = 1;
		bestSquare[1][1] = k;
		bestSquare[1][2] = k;
		setSquare(my_n, k, k, m, 3, square);
		bestSquare[2][0] = k + 1;
		bestSquare[2][1] = k + 1;
		bestSquare[2][2] = m;
		p = findEmptySquare(0, my_n - 1, square, my_n);
		minNumSquare = backtracking(square, bestSquare, my_n, p.x, p.y, my_n + 1, 4);
		std::cout << minNumSquare << std::endl;
		for (int i = 0; i < minNumSquare; i++)
        {
			for (int j = 0; j < 3; j++)
				std::cout << bestSquare[i][j] << " ";
			std::cout << std::endl;
		}
    }
	return 0;
}
