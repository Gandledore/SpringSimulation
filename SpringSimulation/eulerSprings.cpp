#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "vect.h"
#include "spring.h"


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

int main(){
    vector<spring> springs{{{1,0,0},.1,1},{{0,1,0},.3,3},{{-1,-1,0},.2,2}}; // springs position,length,constant
    double g=0;                                            //gravity
    double k=0;                                            //dampening
    double m=1;                                                //mass
    double step = .001;                                       //timestep
    double time = 60;
    vect position = {-.2,-.3,0};                              //initial position
    vect p=position;
    vect velocity = {-1,-.25,0};                                //initial velocity
    vect v=velocity;
    vect acc;
    vector<vect> data;
    for(int i=0;i<springs.size();i++){
        springs[i].c/=m;
    }
    for(double t=0;t<time;t+=step){
        acc = acceleration(position, velocity, springs, g, k,m);
        position = position + velocity*step;
        velocity = velocity + acc*step;
        data.push_back(position);
    }
    ofstream myfile("euler.m");
    myfile << "x=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].x << ",";
    }
    myfile<<data[data.size()-1].x<< "];\ny=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].y << ",";
    }
    myfile << data[data.size()-1].y<<"];\nplot(x,y);\nhold on;\nplot("<<p.x<<","<<p.y<<",\"r.\",'Markersize',10);\n";
    for(int i=0;i<springs.size();i++){
        myfile<<"plot(" << springs[i].position.x << ","<<springs[i].position.y<<",\"k.\",'Markersize',10);\n";
        myfile<<"text(" << springs[i].position.x << ","<<springs[i].position.y<<",\"Equilibrium Length: "<< springs[i].length << "\"+newline+\""<<"Spring Constant: " << springs[i].c*m<<"\");";
    }
    myfile << "\n[t,s] = title(\"Position of Mass Held by " << springs.size() << " Springs for " << time << " Seconds\",\"Mass: "<<m<<"\"+newline+\"Timestep: "<<step<< "\"+newline+\"Dampening: " << k << "\"+newline+\"Initial Vectors: "<<p<< " | " << v<<"\");\n";
    myfile << "quiver("<< p.x<<","<<p.y<<","<<v.x<<","<<v.y<<",'r');\n";
    myfile.close();
    return 0;
}
