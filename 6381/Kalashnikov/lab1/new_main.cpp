#include <iostream>
#include <vector>

using namespace std;

class Square {

    int N, minSquares, currentAmount, scale;
    vector<vector<int>> map;
    vector<vector<int>> answer;
    
    public:

    Square(int size)
     : N(size)
     , map(size, vector<int>(size, 0))
     , minSquares(size*size + 1)
     , answer(size*size, vector<int>(3, 0))
     , currentAmount(0)
     , scale(1)
    {
        if (size%2 == 0)
        {
            scale = size/2;
            N = 2;
        } else if (size%3 == 0) 
        {
            scale = size/3;
            N = 3;
        } else if (size%5 == 0) 
        {
            scale = size/5;
            N = 5;
        } else if (size%2 == 1)   
            preset();
    }

    void print_result()
    {
        cout << minSquares << endl;

    for (int i = 0; i < minSquares; i++)
        cout << answer[i][0] << " " << answer[i][1] << " " << answer[i][2] << endl;
   }

    void recursive_search(int x, int y)
    {
        if (currentAmount == minSquares) 
        {
            return;
        }

        for ( ; x < N; x++)
        {
            for ( ; y < N; y++)
            {
                if (is_cell_empty(x, y))
                {
                    if (y > 0 && is_cell_empty(x, y - 1)) return;

                    for (int m = 1; m < N; m++)
                    {
                        if ( m == 1 ||
                           ( is_cell_empty(x + m - 1, y + m - 1) &&  
                             is_cell_empty(x        , y + m - 1) &&  
                             is_cell_empty(x + m - 1, y        ) ))
                        {
                            place_new_square(m, x, y);
                            recursive_search(   x, y);
                            remove_square   (m, x, y);
                        }
                        else 
                        {
                            return;
                        }
                    }
                }

            }
            y = 0;
        }

        if (is_map_filled())
        {           
            if (currentAmount < minSquares) minSquares = currentAmount;
            update_result_table();
        }
    }

    void update_result_table()
    {
        int m = 1;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (map[i][j] == m)
                {
                    int x = i;
                    
                    while(x < N && map[x][j] == m)
                    {
                        x++;
                    }

                    answer[m-1][0] = scale * i + 1;
                    answer[m-1][1] = scale * j + 1;
                    answer[m-1][2] = scale * (x - i);

                    m++;
                    i = 0;
                    j = 0;
                }
            }
        }
    }

    void preset()
    {
                        // size , x      , y      
        place_new_square((N+1)/2, 0      , 0      );
        place_new_square((N-1)/2, 0      , (N+1)/2);
        place_new_square((N-1)/2, (N+1)/2, 0      );
    }

    bool is_map_filled()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (map[i][j] == 0) return false;
            }
        }
        return true;
    }

    void place_new_square(int m, int x, int y)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                map[i + x][j + y] = currentAmount + 1;
            }
        }

        currentAmount++;
    }

    void remove_square(int m, int x, int y)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                map[i + x][j + y] = 0;
            }
        }

        currentAmount--;
    }

    bool is_cell_empty(int x, int y)
    {
        if( x >= N || y >= N || map[x][y] )
            return false;
        else
            return true;
    }
};

int main()
{
    int N;
    cin >> N;

    Square obj(N);
    obj.recursive_search(0, 0);
    obj.print_result();

    return 0;
}