#include <vector>
#include "vect.h"
#include "spring.h"
#include "write.h"
#include "acceleration.h"
#include "conditions.h"

using namespace std;

int main(){
    vect acc;
    for(int i=0;i<springs.size();i++){
        springs[i].c/=C[2];
    }
    for(double t=0;t<C[4];t+=C[3]){
        acc = acceleration(state.position, state.velocity, springs, C[0], C[1]);
        state.position = state.position + state.velocity*C[3];
        state.velocity = state.velocity + acc*C[3];
        myData.push_back(state.position);
    }
    writeToFile("euler.m",myData,springs,s.position,s.velocity,C,"Euler's Method");
    return 0;
}
