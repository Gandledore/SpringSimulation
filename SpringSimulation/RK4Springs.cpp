#include <vector>
#include "vect.h"
#include "spring.h"
#include "write.h"
#include "acceleration.h"
#include "state.h"
#include "conditions.h"

using namespace std;


State<vect> RK4(State<vect> v,vector<spring> springs, double g, double k){
    vect acc = acceleration(v.position,v.velocity,springs,g,k);
    v.position=v.velocity;
    v.velocity=acc;
    return v;
}

int main(){
    State<vect> k1,k2,k3,k4;
    for(int i=0;i<springs.size();i++){
        springs[i].c/=C[2];
    }
    for(double t=0;t<C[4];t+=C[3]){
        k1=RK4(state,springs,C[0],C[1]);
        k2=RK4(state+k1*(C[3]/2),springs,C[0],C[1]);
        k3=RK4(state+k2*(C[3]/2),springs,C[0],C[1]);
        k4=RK4(state+k3*C[3],springs,C[0],C[1]);

        state = state + (k1+k2*2+k3*2+k4)*(C[3]/6);
        myData.push_back(state.position);
    }
    writeToFile("RK4.m",myData,springs,s.position,s.velocity,C,"RK4");
    return 0;
}
