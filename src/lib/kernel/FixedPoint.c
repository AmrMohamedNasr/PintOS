#include "FixedPoint.h"


 fixed_point fixed_point_mul(fixed_point x, fixed_point y) {
    // right shift 14 bits after multiplication.
    //to return correct fixed point representation of result.
    return ( x  *  y ) >> Fixed_Point_FBits;
}
 fixed_point fixed_point_div(fixed_point x, fixed_point y) {
    // left shift 14 bits before division.
    // to void error and it returns the correct representation of fixed point.
    return (  x << Fixed_Point_FBits ) / y  ;
}

fixed_point integer_to_fixed_point(int x) {
    return x << Fixed_Point_FBits;
}

int fixed_point_to_integer(fixed_point x) {
    return x >> Fixed_Point_FBits;
}

int round_fixed_point_number_to_integer(fixed_point x) {
    if ( (x >> 14) >= 0 ) {
     return ((x + (((fixed_point) 1) << (Fixed_Point_FBits - 1))) >> Fixed_Point_FBits);
    }
    return ((x - (((fixed_point) 1) << (Fixed_Point_FBits - 1))) >> Fixed_Point_FBits);
}
