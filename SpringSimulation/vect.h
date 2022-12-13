#ifndef vect_h
#define vect_h

#include <cmath>
#include <iostream>
struct vect{
    double x;
    double y;
    double z;
    vect(){
        x=0;
        y=0;
        z=0;
    }
    vect(double x, double y, double z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    vect(const vect& other){
        x=other.x;
        y=other.y;
        z=other.z;
    }
    double magnitude(){
        return std::sqrt(x*x+y*y+z*z);
    }
    vect& operator=(const vect& other){
        x=other.x;
        y=other.y;
        z=other.z;
        return *this;
    }
    vect& operator=(const int n){
        x=n;
        y=n;
        z=n;
        return *this;
    }
    vect operator+(const vect& other){
        return {this->x+other.x,this->y+other.y,this->z+other.z};
    }
    vect operator-(const vect& other){
        return {this->x-other.x,this->y-other.y,this->z-other.z};
    }
    vect operator*(double c){
        return {this->x*c,this->y*c,this->z*c};
    }
};
std::ostream& operator<<(std::ostream& os,vect& v){
    os <<v.x <<", "<<v.y<<", " << v.z; 
    return os;
}
#endif