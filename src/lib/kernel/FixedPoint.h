#ifndef FIXEDPOINT_INCLUDED
#define FIXEDPOINT_INCLUDED

#include<stdint.h>
// representation of fixed point.
#define Fixed_Point_FBits 14
#define fixed_point_sub (x, y)  ( (x) - (y) )
#define fixed_point_add (x, y)  ( (x) + (y) )
#define fixed_point_mul (x,y) (( (fixed_point_e)x  * (fixed_point_e) y ) >> Fixed_Point_FBits)
#define fixed_point_div (x, y) ((  (fixed_point_e)x << Fixed_Point_FBits ) / (fixed_point_e)y)
#define integer_to_fixed_point (x) (x << Fixed_Point_FBits)
#define fixed_point_to_integer (x) (x >> Fixed_Point_FBits)
#define round_fixed_point_number_to_integer(x) \
           ((x >> 14) >= 0  ? \
            ((x + (((fixed_point) 1) << (Fixed_Point_FBits - 1))) >> Fixed_Point_FBits) : \
            ((x - (((fixed_point) 1) << (Fixed_Point_FBits - 1))) >> Fixed_Point_FBits) )
/**
 * new data type named fixed point.
 */
typedef int32_t fixed_point;
/**
 * new data type named fixed point extend.
 */
typedef int64_t fixed_point_e;

///**
// * multiplies two fixed point numbers.
// */
// fixed_point fixed_point_mul(fixed_point x, fixed_point y);
///**
// * divides two fixed point numbers.
// */
// fixed_point fixed_point_div(fixed_point x, fixed_point y);
///**
// * it converts from integer to fixed point and return a fixed point value.
// */
//fixed_point integer_to_fixed_point(int x);
///**
// * it converts from fixed point to integer and return integer value.
// */
//int fixed_point_to_integer(fixed_point x);
///**
// * rounds fixed point number to nearest integer.
// *
// */
//int round_fixed_point_number_to_integer(fixed_point x);
#endif // FIXEDPOINT_INCLUDED
