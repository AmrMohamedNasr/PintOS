#ifndef FIXEDPOINT_INCLUDED
#define FIXEDPOINT_INCLUDED

#include<stdint.h>
// representation of fixed point.

/**
 * new data type named fixed point.
 */
typedef int32_t fixed_point;

/**
 * multiplies two fixed point numbers.
 */
 fixed_point fixed_point_mul(fixed_point x, fixed_point y);
/**
 * divides two fixed point numbers.
 */
 fixed_point fixed_point_div(fixed_point x, fixed_point y);



#endif // FIXEDPOINT_INCLUDED
