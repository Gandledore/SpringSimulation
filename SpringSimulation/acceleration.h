#ifndef acceleration_h
#define acceleration_h

#include <vector>
#include "spring.h"
#include "vect.h"

vect acceleration(vect position, vect velocity, std::vector<spring> springs, double g, double k){
    vect acc;
    for(int i=0;i<springs.size();i++){//spring forces
        acc = acc + ((springs[i].position-position)*(springs[i].c)*(1-springs[i].length/(springs[i].position-position).magnitude()));
    }
    acc = acc - velocity*k;//dampening force
    acc.z-=g;//gravity
    return acc;
}

#endif