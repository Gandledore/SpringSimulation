#ifndef conditions_h
#define conditions_h

#include <vector>
#include "spring.h"
#include "vect.h"
#include "state.h"

std::vector<spring> springs{{{1,0,0},.1,1},{{0,1,0},.3,3},{{-1,-1,0},.2,2},{{0,0,-1},1,5}}; // springs position,length,constant
std::vector<double> C = {1,0,1,.001,60}; // gravity, dampening, mass, timestep, simulation time
State<vect> state = {{-.2,-.3,0},{-2,-.5,0}};                              //initial state: position, velocity
State<vect> s = state;
std::vector<vect> myData;
#endif