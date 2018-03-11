#include <iostream>
#include <cmath>

using namespace std;

class Table {
private:
    int** table;
public:
    int field_size;
    int minimum_square_num = 40;
    int** minimum_table;

    bool hasEmptySquare(int& x, int& y);

    void removeSquare(int x, int y, int size);

    void saveSolution(int square_num);

    void fillSquares(int x, int y);

    bool setSquare(int x, int y, int size, int number);

    explicit Table(int size) : field_size(size), table(new int* [size]), minimum_table(new int* [size]) {
        for(int i = 0; i < size; i++) {
            table[i] = new int[size];
            minimum_table[i] = new int[size];
            for(int j = 0; j < size; j++) {
                table[i][j] = 0;
                minimum_table[i][j] = 0;
            }
        }
    }
};

int main() {
    int size, num, k;
    cin >> num;
    if(num % 2 == 0) {
        size = 2;
    } else if(num % 3 == 0) {
        size = 3;
    } else if(num % 5 == 0) {
        size = 5;
    } else {
        size = num;
    }
    if(size == num) {
        k = 1;
    } else {
        k = num / size;
    }

    auto* square_table = new Table(size);
    if(size % 2 == 0) {
        square_table->setSquare(0, 0, size / 2, 1);
        square_table->setSquare(size / 2, 0, size / 2, 2);
        square_table->setSquare(0, size / 2, size / 2, 3);
        square_table->setSquare(size / 2, size / 2, size / 2, 4);
        square_table->saveSolution(4);
    } else {
        square_table->setSquare(0, 0, size / 2 + 1, 1);
        square_table->setSquare(size / 2 + 1, 0, size / 2, 2);
        square_table->setSquare(0, size / 2 + 1, size / 2, 3);
        square_table->fillSquares(size / 2 + 1, size / 2);
    }

    bool need_break = false;
    cout << square_table->minimum_square_num << endl;
    int square_size = 0;
    for(int i = 1; i <= square_table->minimum_square_num; i++) {
        for(int y = 0; y < square_table->field_size; y++) {
            for(int x = 0; x < square_table->field_size; x++) {
                if(square_table->minimum_table[y][x] == i) {
                    cout << y * k + 1 << " " << x * k + 1 << " ";
                    square_size = 1;
                    while(square_table->minimum_table[y][x + square_size] == i && x + square_size < square_table->field_size) {
                        square_size++;
                    }
                    cout << square_size * k << endl;
                    need_break = true;
                    break;
                }
            }
            if(need_break) {
                need_break = false;
                break;
            }
        }
    }
    return 0;
}

void Table::fillSquares(int x, int y) {
    static int square_num = 4;
    if(square_num >= minimum_square_num) {
        return;
    }
    for(int i = field_size / 2; i >= 1; i--) {
        if(setSquare(x, y, i, square_num)) {
            square_num++;
            int next_x = x;
            int next_y = y;
            if(hasEmptySquare(next_x, next_y)) {
                fillSquares(next_x, next_y);
            } else {
                square_num--;
                if(square_num < minimum_square_num) {
                    saveSolution(square_num);
                }
                removeSquare(x, y, i);
                return;
            }
            square_num--;
            removeSquare(x, y, i);
        }
    }
}

bool Table::setSquare(int x, int y, int size, int number) {
    if(y + size > field_size || x + size > field_size) {
        return false;
    }
    for(int i = y; i < y + size; i++) {
        for(int j = x; j < x + size; j++) {
            if(table[i][j] != 0) {
                return false;
            };
        }
    }
    for(int i = y; i < y + size; i++) {
        for(int j = x; j < x + size; j++) {
            table[i][j] = number;
        }
    }
    return true;
}

void Table::removeSquare(int x, int y, int size) {
    for(int i = y; i < y + size; i++) {
        for(int j = x; j < x + size; j++) {
            table[i][j] = 0;
        }
    }
}

bool Table::hasEmptySquare(int& x, int& y) {
    while(table[y][x] != 0) {
        if(x == field_size - 1) {
            if(y == field_size - 1) {
                return false;
            } else {
                y++;
                x = field_size / 2;
                continue;
            }
        }
        x++;
    }
    return true;
}

void Table::saveSolution(int square_num) {
    minimum_square_num = square_num;
    for(int k = 0; k < field_size; k++) {
        for(int m = 0; m < field_size; m++) {
            minimum_table[k][m] = table[k][m];
        }
    }
}
