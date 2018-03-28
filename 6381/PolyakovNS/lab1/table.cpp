void table::print(){
    std::cout<<maxnum<<std::endl;
    for(int i=0;i<maxnum;++i){
        std::cout<<(squares+i)->getld().getx()+1<<" "<<(squares+i)->getld().gety()+1<<" "
        <<(squares+i)->getside()<<std::endl;
    }
}

void table::setmax(){
    maxnum=sidelen+3;
    int n=(sidelen-1)/2;
    squares[0]=square(point(0,0),n+1);
    squares[1]=square(point(n+1,0),n);
    squares[2]=square(point(0,n+1),n);
    squares[3]=square(point(n+1,n+1),n);
    for(int i=0;i<n;++i){
        squares[i+4]=square(point(n+1+i,n),1);
    }
    for(int i=0;i<n;++i){
        squares[n+4+i]=square(point(n,n+1+i),1);
    }
}

table::~table(){
    for(int i=0;i<sidelen;++i){
        delete[] *(array+i);
    }
    delete[] array;
    delete[] squares;
    delete[] current;
}

table::table(){
    num=0;
    sidelen=0;
    maxnum=0;
    array=NULL;
    squares=NULL;
    current=NULL;
}

table::table(int len){
    sidelen=len;
    array = new bool*[len];
    for(int i=0;i<len;++i){
        *(array+i) = new bool[len];
        for(int j=0;j<len;j++){
            *(*(array+i)+j)=false;
        }
    }
    num=0;
    squares=new square[sidelen+3];
    current=new square[sidelen+3];
    maxnum=len+3;
}

void table::zerotable(){
    num=0;
    for(int i=0;i<sidelen;++i){
        for(int j=0;j<sidelen;j++){
            *(*(array+i)+j)=false;
        }
    }
}

inline bool table::get(int x, int y){
    if(x >= sidelen || y >= sidelen) return true;
    return *(*(array+x)+y);
}

inline void table::set(int x, int y, bool val){
    *(*(array+x)+y)=val;
}

bool table::full(){
    for(int i=sidelen-1;i>=0;--i){
        for(int j=sidelen-1;j>=0;--j){
            if(get(i,j)==false) return false;
        }
    }
    return true;
}

point table::findfirstfree(){
    for(int i=0;i<sidelen;++i){
        for(int j=0;j<sidelen;j++){
            if(*(*(array+j)+i) == false) return point(j,i);
        }
    }
    return point();
}


void table::delsquare(square a){
    int x=a.getld().getx();
    int y=a.getld().gety();
    for(int i=x;i<x+a.getside();++i){
        for(int j=y;j<y+a.getside();++j){
            set(i,j,false);
        }
    }
    --num;
}

bool table::addsquare(point a, int size){
    if(size == 1){
        set(a.getx(),a.gety(),true);
        ++num;
        (current+num-1)->setld(a,size);
        return true;
    }
    int x=a.getx();
    int y=a.gety();
    if(get(x+size-1,y)==true || get(x,y+size-1)==true ||
       x+size > sidelen || y+size > sidelen) return false;
    
    for(int i=x;i<x+size;++i){
        for(int j=y;j<y+size;++j){
            set(i,j,true);
        }
    }
    ++num;
    (current+num-1)->setld(a,size);
    return true;
}

void table::nextsquare(){
    if(full()){
        if(num < maxnum){
            maxnum=num;
            for(int i=0;i<maxnum;++i){
                (squares+i)->setld((current+i)->getld(),(current+i)->getside());
            }
        }
        return;
    }
    if(num >= maxnum) return;
    int size=1;
    if(num == 0) size=(sidelen-1)/2;
    point tmp(findfirstfree());
    int x=tmp.getx();
    int y=tmp.gety();
    if(size == 1){
        set(x,y,true);
        ++num;
        (current+num-1)->setld(tmp,size);
        nextsquare();
        delsquare(*(current+num-1));
        ++size;
    }
    if(num==0){
        size=sidelen-2;
        for(;size > 1;){
            if(addsquare(tmp,size) == false){
                return;
            }
            nextsquare();
            delsquare(*(current+num-1));
            --size;
        }
    }
    for(;size < sidelen-1 && x+size-1 < sidelen && y+size-1 < sidelen;){
        if(addsquare(tmp,size) == false){
            return;
        }
        nextsquare();
        delsquare(*(current+num-1));
        ++size;
    }
}


void table::findmin(){
    zerotable();
    
    addsquare(point(0,0),(sidelen+1)/2);
    addsquare(point((sidelen+1)/2,0),(sidelen-1)/2);
    addsquare(point(0,(sidelen+1)/2),(sidelen-1)/2);
    addsquare(point((sidelen+1)/2 - 1,(sidelen+1)/2),1);
    nextsquare();
}








