#ifndef write_h
#define write_h

#include <vector>
#include "spring.h"
#include "vect.h"
#include <fstream>

void writeToFile(std::string fileName, std::vector<vect> data, std::vector<spring> springs, vect p, vect v, std::vector<double> C, std::string method){
    std::ofstream myfile(fileName);
    myfile << "x=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].x << ",";
    }
    myfile<<data[data.size()-1].x<< "];\ny=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].y << ",";
    }
    myfile<<data[data.size()-1].y<< "];\n";
    myfile<<"z=[";
    for(int i=0;i<data.size()-1;i++){
        myfile << data[i].z << ",";
    }
    myfile << data[data.size()-1].z<<"];\n";
    myfile<<"plot3(x,y,z);\n";

    myfile<<"hold on;\nplot("<<p.x<<","<<p.y<<",\"r.\",'Markersize',10);\n";
    for(int i=0;i<springs.size();i++){
        myfile<<"plot3(" << springs[i].position<<",\"k.\",'Markersize',10);\n";
        myfile<<"text(" << springs[i].position<<",\"Equilibrium Length: "<< springs[i].length << "\"+newline+\""<<"Spring Constant: " << springs[i].c*C[2]<<"\");";
    }
    myfile << "\n[t,s] = title(\"Position of Mass Held by " << springs.size() << " Springs for " << C[4] << " Seconds using "<<method<<"\",\"Mass: "<<C[2]<<"\"+newline+\"Timestep: "<<C[3]<< "\"+newline+\"Dampening: " << C[1]<< "\"+newline+\"Gravity: " << C[0] << "\"+newline+\"Initial Vectors: "<<p<< " | " << v<<"\");\n";
    myfile << "quiver("<< p.x<<","<<p.y<<","<<v.x<<","<<v.y<<",'r');\n";
    myfile.close();
}

#endif