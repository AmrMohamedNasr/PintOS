#include "FixedPoint.h"


 fixed_point fixed_point_mul(fixed_point x, fixed_point y) {
    // right shift 14 bits after multiplication.
    //to return correct fixed point representation of result.
    return ( x  *  y ) >> 14;
}
 fixed_point fixed_point_div(fixed_point x, fixed_point y) {
    // left shift 14 bits before division.
    // to void error and it returns the correct representation of fixed point.
    return (  x << 14 ) / y  ;
}
