#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int bestNum = 0;

class Square
{
	int size;
	int **square;
	int numSquare;
public:
	Square(int size) : square(nullptr), size(size), numSquare(0){
		if(size != 0){
			square = new int *[size];
			for (size_t i = 0; i < size; ++i)
				square[i] = new int[size];
			for (size_t i = 0; i < size; ++i)
				for (int j = 0; j < size; ++j)
					square[i][j] = 0;
			constSquares();
		}
	}
	Square (Square const &other): size(other.size), square(nullptr), numSquare(other.numSquare) {
        square = new int*[size];
        for (int i = 0; i < size; i++)
            square[i] = new int[size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                square[i][j] = other.square[i][j];
    }
    Square& operator=(Square const &other){
        if(&other != this){
            for(int i = 0; i < size;i++)
                delete[] square[i];
            delete[] square;
        }
        numSquare = other.numSquare;
        size = other.size;
        square = new int*[size];
        for(size_t i = 0; i < size; ++i){
            square[i] = new int [size];
        }
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                square[i][j] = other.square[i][j];
    }
    ~Square(){
        for(int i = 0; i < size;i++)
            delete[] square[i];
        delete[] square;
        square = nullptr;
        size = 0;
        numSquare = 0;
    }
	void constSquares(){
        int temp = size/2;
        putIn(0, 0, temp+1);
        putIn(0, temp+1, temp);
        putIn(temp+1, 0, temp);
    }
	int getnumSquare(){
		return numSquare;
	}
	int getSize(){
		return size;
	}
	bool isPossible(int i, int j, int k){
		if ((i + k) > size || (j + k) > size)
			return false;
		for (int l = i; l < i + k; l++)
			for (int m = j; m < j + k; m++)
				if (square[l][m] != 0)
					return false;
		return true;
	}
	bool isFreeCell(int i, int j){
		for (int l = i; l < size; l++)
			for (int m = 0; m < size; m++)
				if (square[l][m] == 0)
					return true;
		return false;

	}
	int getNFI(int i, int j){
		for (int l = i; l < size; l++)
			for (int m = 0; m < size; m++)
				if (square[l][m] == 0)
					return l;
	}
	int getNFJ(int i, int j){
		for (int l = i; l < size; l++)
			for (int m = 0; m < size; m++)
				if (square[l][m] == 0)
					return m;
	}
	
	void putIn(int i, int j, int k)// k - size of putted square
	{
		for (int l = i; l < i + k; l++)
			for (int m = j; m < j + k; m++)
				square[l][m] = k;
		numSquare++;
	}
	void zero(int i, int j){
		int k = square[i][j];
		for (int l = i; l < i + k; l++)
			for (int m = j; m < j + k; m++)
				square[l][m] = 0;
	}
	void printSq(){
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				if (square[i][j] != 0)
				{
					cout << i + 1 << " " << j + 1 << " " << square[i][j] << endl;
					zero(i, j);
				}
		}
	}
};

Square best(0);

Square backTracking(Square square, int i, int j){
	for (int k = square.getSize()/2; k > 0; k--)
	{
		if(square.getnumSquare() > bestNum){
            return square;}
		Square condition = square;//fix condition before going next
		if (condition.isPossible(i, j, k))
		{
			condition.putIn(i, j, k);// if it's possible square will be putted into cells
			if (condition.isFreeCell(i, j))//check presence of free cells
				condition = backTracking(condition, condition.getNFI(i, j), condition.getNFJ(i, j));//go to free cell
			else if (condition.getnumSquare() <= bestNum)
			{
				bestNum = condition.getnumSquare();
				best = condition;
			}
		}
	}
	return square;
}
int main()
{
	int size;
	cin >> size;
 	if (size%2 == 0){
        int temp = size/2;
        cout << "4" << endl;
        cout << "1 1 " << temp << endl;
        cout << temp+1 << " 1 " << temp << endl;
        cout << "1 " << temp+1 << " " << temp << endl;
        cout << temp+1 << " " << temp+1 << " "<< temp << endl;
        return 0;
    }
    if (size%3 == 0){
        int temp = size/3;
        cout << "6" << endl;
        cout << "1" << " 1 " << temp*2 <<  endl;
        cout << "1 " << 1+temp*2 << " " << temp <<  endl;
        cout << 1+temp << " " << 1+temp*2 << " " << temp <<  endl;
        cout << 1+temp*2 << " 1 "  << temp <<  endl;
        cout << 1+temp*2 << " " << 1+temp << " "  << temp <<  endl;
        cout << 1+temp*2 << " " << 1+temp*2 << " " << temp << endl;
        return 0;
    }
	Square square(size);
	bestNum = size*size;
	square = backTracking(square, square.getNFI(0,0), square.getNFJ(0,0));
	cout << bestNum << endl;
	best.printSq();
	return 0;
}