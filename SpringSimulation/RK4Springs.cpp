#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "vect.h"
#include "spring.h"
#include "state.h"

using namespace std;

vect acceleration(vect position, vect velocity, vector<spring> springs, double g, double k, double m){
    vect acc;
    for(int i=0;i<springs.size();i++){//spring forces
        acc = acc + ((springs[i].position-position)*(springs[i].c)*(1-springs[i].length/(springs[i].position-position).magnitude()));
    }
    acc = acc - velocity*k;//dampening force
    acc.z-=g;//gravity
    return acc;
}

State<vect> RK4(State<vect> v,vector<spring> springs, double g, double k, double m){
    vect acc = acceleration(v.position,v.velocity,springs,g,k,m);
    v.position=v.velocity;
    v.velocity=acc;
    return v;
}


int main(){
    double g=0;                                            //gravity
    double k=0;                                            //dampening
    double m=1;                                                //mass
    double step = .001;                                       //timestep
    double time = 60;
    vector<spring> springs{{{1,0,0},.1,1},{{0,1,0},.3,3},{{-1,-1,0},.2,2}}; // springs position,length,constant
    State<vect> state = {{-.2,-.3,0},{-1,-.25,0}};                              //initial state
    State<vect> s = state;
    vector<vect> data;
    State<vect> k1,k2,k3,k4;
    for(int i=0;i<springs.size();i++){
        springs[i].c/=m;
    }
    vect acc;
    for(double t=0;t<time;t+=step){
        k1=RK4(state,springs,g,k,m);
        k2=RK4(state+k1*(step/2),springs,g,k,m);
        k3=RK4(state+k2*(step/2),springs,g,k,m);
        k4=RK4(state+k3*step,springs,g,k,m);

        state = state + (k1+k2*2+k3*2+k4)*(step/6);
        data.push_back(state.position);
    }
    ofstream myfile("RK4.m");
    myfile << "x=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].x << ",";
    }
    myfile<<data[data.size()-1].x<< "];\ny=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].y << ",";
    }
    myfile << data[data.size()-1].y<<"];\nplot(x,y);\nhold on;\nplot("<<s.position.x<<","<<s.position.y<<",\"r.\",'Markersize',10);\n";
    for(int i=0;i<springs.size();i++){
        myfile<<"plot(" << springs[i].position.x << ","<<springs[i].position.y<<",\"k.\",'Markersize',10);\n";
        myfile<<"text(" << springs[i].position.x << ","<<springs[i].position.y<<",\"Equilibrium Length: "<< springs[i].length << "\"+newline+\""<<"Spring Constant: " << springs[i].c*m<<"\");";
    }
    myfile << "\n[t,s] = title(\"Position of Mass Held by " << springs.size() << " Springs for " << time << " Seconds using RK4\",\"Mass: "<<m<<"\"+newline+\"Timestep: "<<step<< "\"+newline+\"Dampening: " << k << "\"+newline+\"Initial Vectors: "<<s.position<< " | " << s.velocity<<"\");\n";
    myfile << "quiver("<< s.position.x<<","<<s.position.y<<","<<s.velocity.x<<","<<s.velocity.y<<",'r');\n";
    myfile.close();
    return 0;
}
