#include <iostream>
#include <vector>

using namespace std;

class Number
{
	int number;
	int scale;
	int numberInTable;
	vector<int> squares;
	vector<int> numberOfSquares;

public:
	Number(int number, int primeDivisor, int numberInTable, vector<int> squares, vector<int> numberOfSquares)
	{
		this->number = number;
		this->scale = number/primeDivisor;
		this->numberInTable = numberInTable;
		this->squares = squares;
		this->numberOfSquares = numberOfSquares;
	}
	~Number()
	{
		squares.erase(squares.begin(), squares.begin() + squares.size());
		numberOfSquares.erase(numberOfSquares.begin(), numberOfSquares.begin() + squares.size());
	}
	int getScale()
	{
		return scale;
	}
	int getNumberInTable()
	{
		return numberInTable;
	}
	int getPrimeDivisor()
	{
		return number/scale;
	}
	vector<int> getSquares()
	{
		return squares;
	}
	vector<int> getNumberOfSquares()
	{
		return numberOfSquares;
	}
};

Number divisionByPrimeNumber(int n)
{
	vector<vector<int>> squares = {
		{ 1 },
		{ 1, 2 },
		{ 1, 2 ,3 },
		{ 1, 2, 3, 4 },
		{ 1, 2, 3, 5, 6 },
		{ 1, 2, 3, 4, 6, 7 },
		{ 1, 2, 3, 4, 5, 8, 9 },
		{ 1, 3, 4, 5, 6, 9, 10 },
		{ 1, 2, 3, 4, 6, 7, 10, 13 },
		{ 1, 3, 4, 5, 6, 7, 13, 16 },
		{ 1, 2, 4, 8, 15, 16 },
		{ 2, 3, 4, 5, 9, 11, 17, 20 }
	};

	vector<vector<int>> numberOfSquares = {
		{ 4 },
		{ 5, 1 },
		{ 4, 3, 1 },
		{ 3, 3, 2, 1 },
		{ 4, 1, 3, 2, 1 },
		{ 2, 3, 2, 1, 2, 1 },
		{ 2, 3, 1, 2, 1, 2, 1 },
		{ 1, 4, 2, 3, 1, 1, 1 },
		{ 2, 3, 1, 1, 2, 1, 2, 1 },
		{ 1, 2, 2, 3, 2, 1, 2, 1 },
		{ 3, 3, 3, 3, 2, 1 },
		{ 2, 3, 3, 1, 2, 1, 2, 1 }
	};

	int primeNumbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (int i = 0; i < 12; i++)
		if (n%primeNumbers[i] == 0)
			return Number(n, primeNumbers[i], i,squares[i], numberOfSquares[i]);
}

class Table
{
	int size;
	int result = 0;
	int scale;
	vector<vector<int>> table;
	vector<int> squares;
	vector<int> numberOfSquares;
public:
	Table (Number number) : size(number.getPrimeDivisor())
	{
		this->scale = number.getScale();
		table.resize(size);
		for (unsigned i = 0; i < table.size(); i++)
			table[i].resize(size);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				table[i][j] = 0;
		this->squares = number.getSquares();
		this->numberOfSquares = number.getNumberOfSquares();
		for (int i = 0; i < numberOfSquares.size(); i++)
			result += numberOfSquares[i];
	}
	~Table()
	{
		squares.erase(squares.begin(), squares.begin() + squares.size());
		numberOfSquares.erase(numberOfSquares.begin(), numberOfSquares.begin() + squares.size());
	}

	int getSquaresSize()
	{
		return squares.size();
	}

	int getNextI(int i, int j)
	{
		for (int l = i; l < size; l++)
			for (int m = 0; m < size; m++)
				if (table[l][m] == 0)
					return l;
	}

	int getNextJ(int i, int j)
	{
		for (int l = i; l < size; l++)
			for (int m = 0; m < size; m++)
				if (table[l][m] == 0)
					return m;
	}
	void putSquare(int i, int j, int k)// squares[k] - size of putted square
	{
		for (int l = i; l < i + squares[k]; l++)
			for (int m = j; m < j + squares[k]; m++)
				table[l][m] = squares[k];
		//printSquare();
		//cout << endl;
		if (numberOfSquares[k] != 1)
		{
			numberOfSquares[k]--;//decrease number of squares in the vector
		}
		else
		{
			numberOfSquares.erase(numberOfSquares.begin() + k);//if it was the last square delete it from the vector
			squares.erase(squares.begin() + k);
		}
	}
	bool isPossible(int i, int j, int k)
	{
		if ((i + squares[k]) > size || (j + squares[k]) > size)
			return false;
		for (int l = i; l < i + squares[k]; l++)
			for (int m = j; m < j + squares[k]; m++)
				if (table[l][m] != 0)
					return false;
		return true;
	}
	bool isFreeCell(int i, int j)
	{
		for (int l = i; l < size; l++)
			for (int m = 0; m < size; m++)
				if (table[l][m] == 0)
					return true;
		return false;

	}

	void printSquare()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				cout << table[i][j];
			cout << endl;
		}
	}
	void zero(int i, int j)
	{
		int k = table[i][j];
		for (int l = i; l < i + k; l++)
			for (int m = j; m < j + k; m++)
				table[l][m] = 0;
	}
	void printAllSquares()
	{
		cout << result << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				if (table[i][j] != 0)
				{
					cout << i*scale + 1 << " " << j*scale + 1 << " " << table[i][j]*scale << endl;
					zero(i, j);
				}
		}
	}
};


bool wasFound = false;// the variable was added to exit the recursive function

Table backTracking(Table table, int i, int j)
{
	if (!wasFound)
	{
		for (int k = table.getSquaresSize() - 1; k >= 0; k--)//
		{
			Table condition = table;//fix condition before going next
			if (condition.isPossible(i, j, k))// check possibility to put a square with size, which is in vector[k], into cell(i, j)
			{
				condition.putSquare(i, j, k);// put the square in the table
				if (condition.isFreeCell(i, j))//check presence of free cells
					condition = backTracking(condition, condition.getNextI(i, j), condition.getNextJ(i, j));//go to free cell
				else
				{
					condition.printAllSquares();// if there isn't possibility to put the square into the table, that means configuration was founded
					wasFound = true; //to exit the recursive function
					break;
				}
			}
		}
	}
	return table;
}

int main()
{
	int n;
	std::cin >> n;
	Number number = divisionByPrimeNumber(n);//find prime divisor and work with it instead of N
	Table table (number);
	table = backTracking(table, 0, 0);
    return 0;
}
