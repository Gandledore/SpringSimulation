#ifndef state_h
#define state_h

#include <iostream>
template<class T>
struct State{
    T position;
    T velocity;
    State(){
        position=0;
        velocity=0;
    }
    State(T position, T velocity){
        this->position=position;
        this->velocity=velocity;
    }
    State(const State<T>& other){
        position=other.position;
        velocity=other.velocity;
    }
    State<T>& operator=(const State<T>& other){
        position=other.position;
        velocity=other.velocity;
        return *this;
    }
    State<T> operator+(const State<T>& other){
        return {this->position+other.position,this->velocity+other.velocity};
    }
    State<T> operator-(const State<T>& other){
        return {this->position-other.position,this->velocity-other.velocity};
    }
    State<T> operator*(double c){
        return {this->position*c,this->velocity*c};
    }
};
template<class T>
std::ostream& operator<<(std::ostream& os,State<T>& v){
    os << "(" <<v.position <<", "<<v.velocity<<")"; 
    return os;
}
#endif