#include <iostream>
#include <cmath>

class Table;
void makeFullTable(int size, Table* &table);
void printResult(int coef, Table* &table);

using namespace std;

class Table
{
private:
    int** table;

public:
    int table_size;
    int min_table_num = 40;
    int** min_table;

    explicit Table(int size) : table_size(size), table(new int* [size]), min_table(new int* [size])
    {
        for(int i = 0; i < size; i++)
        {
            table[i] = new int[size];
            min_table[i] = new int[size];
            for(int j = 0; j < size; j++)
            {
                table[i][j] = 0;
                min_table[i][j] = 0;
            }
        }
    }

    void setZeroTable(int x, int y, int size)
    {
        for(int i = y; i < y + size; i++)
        {
            for(int j = x; j < x + size; j++) table[i][j] = 0;
        }
    }

    void saveTable(int table_num)
    {
        min_table_num = table_num;
        for(int i = 0; i < table_size; i++)
        {
            for(int m = 0; m < table_size; m++) min_table[i][m] = table[i][m];
        }
    }

    void fillTable(int x, int y)
    {
        static int table_num = 4;
        if(table_num >= min_table_num) return;
        for(int i = table_size / 2; i >= 1; i--)
        {
            if(setTable(x, y, i, table_num))
            {
                table_num++;
                int next_x = x;
                int next_y = y;
                if(findZeroTable(next_x, next_y)) fillTable(next_x, next_y);
                else
                {
                    table_num--;
                    if(table_num < min_table_num) saveTable(table_num);
                    setZeroTable(x, y, i);
                    return;
                }
                table_num--;
                setZeroTable(x, y, i);
            }
        }
    }

    bool findZeroTable(int& x, int& y)
    {
        while(table[y][x] != 0)
        {
            if(x == table_size - 1)
            {
                if(y == table_size - 1) return false;
                else 
                {
                    y++;
                    x = table_size / 2;
                    continue;
                }
            }
            x++;
        }
        return true;
    }

    bool setTable(int x, int y, int size, int number)
    {
        if(y + size > table_size || x + size > table_size) return false;
        for(int i = y; i < y + size; i++)
        {
            for(int j = x; j < x + size; j++)
            {
                if(table[i][j] != 0) return false;
            }
        }
        for(int i = y; i < y + size; i++)
        {
            for(int j = x; j < x + size; j++) table[i][j] = number;
        }
        return true;
    }
};

void makeFullTable(int size, Table* &table)
{
    if(size % 2 == 0)
    {
        table->setTable(0, 0, size / 2, 1);
        table->setTable(size / 2, 0, size / 2, 2);
        table->setTable(0, size / 2, size / 2, 3);
        table->setTable(size / 2, size / 2, size / 2, 4);
        table->saveTable(4);
    }
    else
    {
        table->setTable(0, 0, size / 2 + 1, 1);
        table->setTable(size / 2 + 1, 0, size / 2, 2);
        table->setTable(0, size / 2 + 1, size / 2, 3);
        table->fillTable(size / 2 + 1, size / 2);
    }
}

void printResult(int coef, Table* &table)
{   
    bool table_found = false;
    int table_size = 0;
    cout << table->min_table_num << endl;
    
    for(int i = 1; i <= table->min_table_num; i++)
    {
        table_found = false;
        for(int y = 0; y < table->table_size; y++)
        {
            for(int x = 0; x < table->table_size; x++)
            {
                if(table->min_table[y][x] == i)
                {
                    cout << y * coef + 1 << " " << x * coef + 1 << " ";
                    table_size = 1;
                    while(table->min_table[y][x + table_size] == i && x + table_size < table->table_size) table_size++;
                    cout << table_size * coef << endl;
                    table_found = true;
                    break;
                }
            }
            if(table_found) break;
        }
    }
}

int main()
{
    int size, num, coef;
    cin >> num;
    num % 2 == 0 ? size=2 : num % 3 == 0 ? size=3 : num % 5 == 0 ? size=5 : size=num;
    coef = num / size;

    auto* table = new Table(size);
    makeFullTable(size, table);
    printResult(coef, table);
    
    return 0;
}