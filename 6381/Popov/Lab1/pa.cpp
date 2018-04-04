#include <iostream>
#include <vector>

using namespace std;

class Board{
	int boardSize;
	int currAmountSq = 0;
	vector<vector<int>> busyCells;
	int smallestAmountSq;
	vector<vector<int>> bestBoard;
	
	bool findFreeCell(int &x, int &y);
	bool exitFromBounds(int x, int y, int width);
	bool buildSq(int x, int y, int width);
	void deleteSq(int x, int y);
	void changeBestBoard();
	int findSq(int& x, int& y, int K);
public:
	Board(int);
	void printBestBrd();
	friend void squaring(Board *board, int x, int y);
	friend void modSquaring(Board *board);
	friend void printList(Board *board);
};

Board::Board(int sqs) : boardSize(sqs), smallestAmountSq(0){
	busyCells.resize(boardSize, vector<int>(boardSize, 0));
	bestBoard.resize(boardSize, vector<int>(boardSize, 0));
	smallestAmountSq = boardSize * boardSize + 1;
}

void Board::printBestBrd(){
	for(int i = boardSize - 1;i > -1; i--){
		for(int j = 0; j < boardSize; j++)
			cout << bestBoard[i][j];
		cout << endl;
	}
}

int Board::findSq(int& x, int& y, int num){
    while (bestBoard[y][x] != num){
        if (x == boardSize - 1){
            x = 0;
            ++y;
        }
        else 
			++x;
        if (x >= boardSize || y >= boardSize)
            return 0;
    }
    int i = 0;
    while (bestBoard[y][x+i] == num){
        if ((x+i)<boardSize)
            ++i;
        else
			return --i;
    }
    return i;
}
	
void Board::changeBestBoard(){
	smallestAmountSq = currAmountSq - 1;
	bestBoard = busyCells;
}

bool Board::findFreeCell(int &x, int &y){
	while (busyCells[y][x]){
        if (x == boardSize - 1){
            x = 0;
            ++y;
        }
        else 
			++x;
        if (x >= boardSize || y >= boardSize)
            return 0;
    }
    return 1;
}

bool Board::exitFromBounds(int x, int y, int width){
    return (width > boardSize-x || width > boardSize-y);
}

bool Board::buildSq(int x, int y, int width){
    if (exitFromBounds(x, y, width)) 
		return 0;
    for(int i = 0; i < width; i++)
        for (int j = 0; j < width; j++)
            if (!busyCells[y+i][x+j])
                busyCells[y+i][x+j] = currAmountSq;
            else{
                deleteSq(x, y);
                return 0;
            }
	++currAmountSq;
    return 1;
}

void Board::deleteSq(int x, int y){
    for(int i = y; i < boardSize && busyCells[i][x] == currAmountSq; i++)
        for (int j = x; j < boardSize && busyCells[i][j] == currAmountSq; j++)
            busyCells[i][j] = 0;
}

void squaring(Board *board, int x = 0, int y = 0){
    if (board->currAmountSq > board->smallestAmountSq)
		return;
	if(board->findFreeCell(x, y)){
		for(int width = board->boardSize - 1; width > 0; width--){
			if(board->buildSq(x, y, width)){
				squaring(board, x, y);
				--board->currAmountSq;
			}
			board->deleteSq(x, y);
		}
	}
	else
		if(board->currAmountSq - 1 < board->smallestAmountSq)
			board->changeBestBoard();
}

void modSquaring(Board *board){
	int size = board->boardSize;
	if (size % 2 == 0){
        cout << 4 << endl;
        cout << 1        << " " << 1        << " " << size/2 << endl;
        cout << 1        << " " << size/2+1 << " " << size/2 << endl;
        cout << size/2+1 << " " << 1        << " " << size/2 << endl;
        cout << size/2+1 << " " << size/2+1 << " " << size/2 << endl;
    }
    else if (size % 3 == 0){
        cout << 6 << endl;
        cout << 1        << " " << 1        << " " << 6*size << endl;
        cout << 6*size+1 << " " << 1        << " " << 3*size << endl;
        cout << 6*size+1 << " " << 3*size+1 << " " << 3*size << endl;
        cout << 6*size+1 << " " << 6*size+1 << " " << 3*size << endl;
        cout << 3*size+1 << " " << 6*size+1 << " " << 3*size << endl;
        cout << 1        << " " << 6*size+1 << " " << 3*size << endl;
    }
    else if (size % 5 == 0){
        cout << 8 << endl;
        cout << 1         << " " << 1         << " " << 15*size << endl;
        cout << 15*size+1 << " " << 1         << " " << 10*size << endl;
        cout << 15*size+1 << " " << 10*size+1 << " " << 10*size << endl;
        cout << 1         << " " << 15*size+1 << " " << 10*size << endl;
        cout << 10*size+1 << " " << 15*size+1 << " " << 5*size  << endl;
        cout << 10*size+1 << " " << 20*size+1 << " " << 5*size  << endl;
        cout << 15*size+1 << " " << 20*size+1 << " " << 5*size  << endl;
        cout << 20*size+1 << " " << 20*size+1 << " " << 5*size  << endl;
    }
    else{
		++board->currAmountSq;
        board->buildSq(0,        0,        size/2+1);
        board->buildSq(size/2+1, 0,        size/2);
        board->buildSq(0,        size/2+1, size/2);
        board->buildSq(size/2+1, size/2,   1);
		squaring(board, size/2+2, size/2);
		printList(board);
		board->printBestBrd();
    }
}

void printList(Board *board){
	cout << board->smallestAmountSq << endl;
    int x, y, size;
    for(int i = 1; i <= board->smallestAmountSq; i++){
        x = 0;
		y = 0;
        size = board->findSq(x, y, i);
        cout << x+1 << " " << y+1 << " " << size << endl;
    }
}

int main(){
    int size;
    cin >> size;
	Board *board = new Board(size);
	modSquaring(board);
	return 0;
}
