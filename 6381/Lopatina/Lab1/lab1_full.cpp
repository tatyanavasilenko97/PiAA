#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

void removeSquare(int** &squareTmp, int color, int x, int y, int n) { 
	for (int i = y; (i < n) && (squareTmp[i][x] == color); i++) {
		for (int j = x; (j < n) && (squareTmp[i][j] == color); j++)
			squareTmp[i][j] = 0;
	}
}

bool installSquare(int** &squareTmp, int color, int size, int x, int y, int n) { 
	if ((n < x + size) || (n < y + size))
		return false;
		
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (squareTmp[i+y][j+x] != 0)
				return false;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			squareTmp[i + y][j + x] = color;
}

bool findEmptySquare(int** &squareTmp, int& x, int& y, int n) { 
	while (y < n) {
		while (x < n) {
			if (squareTmp[y][x] == 0)
				return true;
			if (x == n - 1) {
				y++;
				x = 0;
				break;
			}
			x++;
		}
	}
	return false;
}

void recurcion(int& min_square, int n, int** &squareTmp, int** &squareBest, int x, int y) { 
	static int temp_square = 1;
	if (temp_square >= min_square)
		return;

	for (int i = 1; i <= n-1; i++) {
		if (installSquare(squareTmp, temp_square, i, x, y, n)) {
			temp_square++;
			int x_1 = x;
			int y_1 = y;
			if (findEmptySquare(squareTmp, x_1, y_1, n))
				recurcion(min_square, n, squareTmp, squareBest, x_1, y_1);
			else {
				temp_square--;
				if (temp_square < min_square) {
					min_square  = temp_square;
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

int main() {
	int n; 
	int length [40] = {0};
	int min_square = 40;
	cin >> n;

	int** squareTmp = new int*[n];
	int** squareBest = new int*[n];
	for (int i = 0; i < n; i++) {
		squareTmp[i] = new int[n];
		squareBest[i] = new int[n];
		for (int j = 0; j < n; j++) {
			squareTmp[i][j] = 0;
			squareBest[i][j] = 0;
		}
	}
		recurcion(min_square, n, squareTmp, squareBest, 0, 0);

		cout << min_square << endl;
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				length[squareBest[i][j]]++;
		for (int i = 0; i<40; i++)
			length[i] = sqrt(length[i]);

		for (int i = 0; i<n; i++){
			for (int j = 0; j<n; j++){
				if (((i==0)&&(j==0))||
					((i==0)&&(squareBest[i][j-1]!=squareBest[i][j]))||
					((j==0)&&(squareBest[i-1][j]!=squareBest[i][j]))||
					((j!=0)&&(i!=0)&&(squareBest[i-1][j]!= squareBest[i][j])&&(squareBest[i][j-1] != squareBest[i][j]))){
						cout << i+1 << " " << j+1 << " " << length[squareBest[i][j]] << endl;
				}
			}
		}	
    return 0;
}