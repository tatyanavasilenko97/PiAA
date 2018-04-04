#include <iostream>
#include <cmath>

class Point {
private:
	int x;
	int y;
public:
	explicit Point(int x, int y) : x(x), y(y) {};
	friend std::ostream& operator<<(std::ostream &out, Point point){
		out << "Point: X = " << point.x << " Y = " << point.y << std::endl;
	}

	int getX() const { 
		return x;
	}

	int getY() const { 
		return y;
	}
};


class Table {
private:
	int size;
	int** table;
	int squaresNumber;
public:
	explicit Table(int size) : size(size), table(nullptr), squaresNumber(0) {
		table = new int*[size];
		for (int i = 0; i < size; i++)
			table[i] = new int[size];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				table[i][j] = 0;
	}

	Table(Table const &rhs): size(rhs.size), table(nullptr), squaresNumber(rhs.squaresNumber) {
		table = new int*[size];
		for (int i = 0; i < size; i++)
			table[i] = new int[size];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				table[i][j] = rhs.table[i][j];
	}

	Table& operator=(Table const &rhs){
		squaresNumber = rhs.squaresNumber;
		size = rhs.size;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				table[i][j] = rhs.table[i][j];
		// Такая оптимальная реализция возможна на счёт того факта, что все таблицы в программе одного размера.
	}

	~Table(){
		for (int i = 0; i < size; i++)
			delete[] table[i];
		delete[] table;
	}

	int getSize() const {
		return size;
	}

	int getNumberOfSquares() const {
		return squaresNumber;
	}

	bool checkForEmptyCell(int i, int j) const {
		if (table[i][j] == 0)
			return true;
		else
			return false;
		// return (!table[i][j]);
	}

	bool canStandSquare(Point point, int sizeOfSquare){
		if ((point.getX() + sizeOfSquare) > size || (point.getY() + sizeOfSquare) > size)
			return false;
		for (int i = 0; i < sizeOfSquare; i++)
			for (int j = 0; j < sizeOfSquare; j++)
				if (table[i+point.getY()][j+point.getX()])
					return false;
		return true;
	}

	void putSquare(Point point, int sizeOfSquare){
		for (int i = 0; i < sizeOfSquare; i++)
			for (int j = 0; j < sizeOfSquare; j++)
				table[i+point.getY()][j+point.getX()] = sizeOfSquare;
		squaresNumber++;
	}

	bool isTableFilled(Point point) const {
		for (int i = point.getY(); i < size; i++)
			for (int j = 0; j < size; j++)
				if (table[i][j] == 0)
					return false;
		return true;

	}

	Point getNextPosition(Point point){
		for (int line = point.getY(); line < size; line++)
			for (int col = 0; col < size; col++){
				if (this->checkForEmptyCell(line, col)){
					// x = col;
					// y = line;
					Point newPoint(col, line);
					return newPoint;
				}
			}
		return point;
	}

	friend std::ostream& operator<<(std::ostream &out, Table &t){
		out << t.squaresNumber << "\n";
		// t.printMatrix();
		t.printSquaresCoordinates();
		return out;
	}

private:
	void printSquaresCoordinates() {
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++)
				if (table[i][j] != 0){
					std::cout << i + 1 << " " << j + 1 << " " << table[i][j] << std::endl;
					zero(i, j);
				}
		}
	}

	void zero(int i, int j){
		int k = table[i][j];
		for (int l = i; l < i + k; l++)
			for (int m = j; m < j + k; m++)
				table[l][m] = 0;
	}

	void printMatrix() const {
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++)
				std::cout << table[i][j] << " ";
			std::cout << "\n";
		}
		std::cout << std::endl;
	}
};

Table* best;

int BackTrack(Table table, Point point){
	static int minNumberOfSquares = pow(table.getSize(), 2);
	static int calls = 0;
	calls++;
	// std::cout << "Call back begin " << point.getY() << " " << minNumberOfSquares << "\n";
	for (int squareSize = 1; squareSize < table.getSize(); squareSize++){
		Table currentState(table);
		if (currentState.canStandSquare(point, squareSize)){
			currentState.putSquare(point, squareSize);
			if (!currentState.isTableFilled(point)  && currentState.getNumberOfSquares() <= minNumberOfSquares)
				BackTrack(currentState, currentState.getNextPosition(point));
			else 
				if (currentState.getNumberOfSquares() <= minNumberOfSquares){
					minNumberOfSquares = currentState.getNumberOfSquares();
					*best = currentState;
				}
		}
	}
	return calls;
}

int main() {
	int SizeOfSquare;
	std::cin >> SizeOfSquare;

	Table table(SizeOfSquare);
	best = new Table(SizeOfSquare);

	int call = BackTrack(table, Point(0,0));
	// std::cout << "Calls: " <<call << std::endl;
	std::cout << *best << std::endl;

	delete best;
	return 0;
}