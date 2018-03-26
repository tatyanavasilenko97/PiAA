point square::getld(){
    return ld;
}

int square::getside(){
    return sidelen;
}

void square::setld(point x, int len){
    sidelen=len;
    ld=x;
}

square::square(){
    ld=point();
    sidelen=0;
}

square::square(point x, int len){
    sidelen=len;
    ld=x;
}

