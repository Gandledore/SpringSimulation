#ifndef spring_h
#define spring_h

#include "vect.h"
struct spring{
    vect position;
    double length; //equilibrium length
    double c;
    spring(){
        length=0;
        c=1;
    }
    spring(vect p,double l,double c){
        position = p;
        length=l;
        this->c=c;
    }
};


#endif