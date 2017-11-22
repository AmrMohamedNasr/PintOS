#include "FixedPoint.h"


 fixed_point fixed_point_mul(fixed_point x, fixed_point y) {
    return ( (fixed_point_e) x * (fixed_point_e) y) >> 14;
}
 fixed_point fixed_point_div(fixed_point x, fixed_point y) {
    return ( (fixed_point_e) x << 14  / (fixed_point_e) y) ;
}
