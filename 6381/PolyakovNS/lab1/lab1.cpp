#include <iostream>
#include "square.hpp"
#include "point.hpp"
#include "table.hpp"


int main(){
    int number;
    std::cin>>number;
    if(number % 2 == 0){
        std::cout<<4<<std::endl;
        std::cout<<1<<" "<<1<<" "<<(int)(number/2)<<std::endl;
        std::cout<<1<<" "<<(int)(number/2)+1<<" "<<(int)(number/2)<<std::endl;
        std::cout<<(int)(number/2)+1<<" "<<1<<" "<<(int)(number/2)<<std::endl;
        std::cout<<(int)(number/2)+1<<" "<<(int)(number/2)+1<<" "<<(int)(number/2)<<std::endl;
        return 0;
    }
    if(number % 3 == 0){
        std::cout<<6<<std::endl;
        std::cout<<1<<" "<<1<<" "<<(int)(number/3)<<std::endl;
        std::cout<<number/3 + 1<<" "<<1<<" "<<(int)(number*2/3)<<std::endl;
        std::cout<<1<<" "<<number/3 + 1<<" "<<(int)(number/3)<<std::endl;
        std::cout<<1<<" "<<number*2/3 + 1<<" "<<(int)(number/3)<<std::endl;
        std::cout<<number/3 + 1<<" "<<number*2/3 + 1<<" "<<(int)(number/3)<<std::endl;
        std::cout<<number*2/3 + 1<<" "<<number*2/3 + 1<<" "<<(int)(number/3)<<std::endl;
        return 0;
    }
    if(number % 5 == 0 ){
        std::cout<<8<<std::endl;
        std::cout<<1<<" "<<1<<" "<<(int)number*3/5<<std::endl;
        std::cout<<number*3/5+1<<" "<<1<<" "<<(int)number*2/5<<std::endl;
        std::cout<<1<<" "<<number*3/5+1<<" "<<(int)number*2/5<<std::endl;
        std::cout<<number*3/5+1<<" "<<number*3/5+1<<" "<<(int)number*2/5<<std::endl;
        
        std::cout<<number*2/5+1<<" "<<(number*3)/5+1<<" "<<number/5<<std::endl;
        std::cout<<number*2/5+1<<" "<<((number)*3)/5+number/5+1<<" "<<number/5<<std::endl;
        std::cout<<(number*3)/5+1<<" "<<number*2/5+1<<" "<<number/5<<std::endl;
        std::cout<<((number+1)*3)/5+number/5+1<<" "<<number*2/5+1<<" "<<number/5<<std::endl;
        return 0;
    }
    table x(number);
    x.setmax();
    x.findmin();
    x.print();
    return 0;
}
