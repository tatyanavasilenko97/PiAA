#include <iostream>
#include <vector>

struct point
{
    point(size_t x = 0, size_t y = 0) : x(x), y(y){}
    size_t x;
    size_t y;
};

struct answer
{
    answer(point p = point(), size_t length = 0) : coord(p), size(length) {}
    size_t size;
    point coord;
};

//Вывод ответа
void printAnswer( std::vector<answer> out )
{
    std::cout << out.size() << '\n';
    for( unsigned i = 0; i < out.size(); ++i )
    std::cout << out[i].coord.x+1 << ' ' << out[i].coord.y+1 << ' ' << out[i].size <<  '\n';
    std::cout << '\n';
}

//Рисование квадрата
size_t fill_rect( std::vector<std::vector<int> >* input_arr, size_t limit, point p, size_t sq_num )
{
    limit = input_arr->size() < limit + std::max(p.x, p.y) ? input_arr->size() - std::max(p.x, p.y) : limit;//??

    for( size_t i = p.y; i < p.y + limit; i++)
        for( size_t  j = p.x; j < p.x + limit; j++)
            if( (*input_arr)[i][j] )
                limit = j - p.x;
            else
                (*input_arr)[i][j] = sq_num;

    return limit;
}

//поиск свободной точки
bool def_free(std::vector<std::vector<int> > input_arr, point* p)
{
    for( size_t i = 0; i < input_arr.size(); i++ )
        for( size_t j = 0; j < input_arr.size(); j++ )
            if (!input_arr[i][j])
            {
                *p = point(j, i);
                return true;
            }
    return false;
}

//Проверка на пустоту
bool fit_tight( std::vector<std::vector<int> > input_arr, point p, size_t rec_size  )
{
    size_t res = 0;

    //Empty floor
    if( p.y + rec_size == input_arr.size() )
        ++res;

    //Empty left
    if( !p.x )
        ++res;
    else
        res += input_arr[p.y + rec_size - 1][p.x - 1] ? 1 : 0;

    //Empty right
    if( p.x + rec_size == input_arr.size() )
        ++res;
    ++res;


    return res >= 3 ? true : false;
}

void print(std::vector<std::vector<int> > data)
{
    for( unsigned int i = 0; i<data.size(); i++ )
    {
        for( unsigned int j = 0; j<data.size(); j++ )
            std::cout << data[i][j] << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

//Основная рекурсивная функция
void trace( std::vector<std::vector<int> > input_arr , size_t boundary, size_t sq_num, std::vector<answer>* ans, std::vector<answer> comp_arr = std::vector<answer>() )
{
    size_t clent = 0;
    point p;

    std::vector<std::vector<int> > beforelast = input_arr;

    if( def_free(input_arr, &p) )
        clent = fill_rect(&input_arr, boundary, p, sq_num);

    if( !fit_tight( input_arr, p, clent ) && boundary > 1 )
        trace(beforelast, boundary - 1, sq_num, ans, comp_arr);

    comp_arr.push_back(answer(p, clent));
    ++sq_num;

    while( def_free(input_arr, &p) )
    {
        beforelast = input_arr;
        clent = fill_rect(&input_arr, input_arr.size() - 1, p, sq_num);

        if( !fit_tight( input_arr, p, clent ) && boundary > 1 )
            trace(beforelast, boundary - 1, sq_num, ans, comp_arr);

        comp_arr.push_back(answer(p, clent));
        ++sq_num;
    }
if( comp_arr.size() < ans->size() ) 
{ 
system("cls"); 
std::cout <<"Recursive iteration number:"<< sq_num << '\n'; 
*ans = comp_arr; 
print(input_arr); 
}
}

int main( void )
{
    size_t n;
    std::cin >> n;

    if( n % 2 == 0 )//для четных 
    {
        std::cout << '4' << '\n';
        std::cout << "0 0" << '\n';
        std::cout << 0 << ' ' << n/2 << '\n';
        std::cout << n/2 << ' ' << 0 << '\n';
        std::cout << n/2 << ' ' << n/2 << '\n';
        return 0;
    }
    else
    {
        std::vector<answer> output;
        std::vector<std::vector<int> > data(n, std::vector<int>(n, 0));

        output.resize(40);
        trace(data, n - 1, 1, &output);

        printAnswer(output);
    }
    return 0;
}
