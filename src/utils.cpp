

#include "utils.hpp"


#define EPSILON 0.00001

bool compare_doubles(double x, double y) { 
    if (fabs(x - y) < EPSILON) { 
	    return true; 
    }
    return false; 
}
