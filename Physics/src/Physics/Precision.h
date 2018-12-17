#pragma once
#include <math.h>

/*
* defines a real number, makes it easy to change from single to double precision
*/
typedef float real;

/*
* defines precision of the square root operator
*/
#define real_sqrt sqrtf

/*
* defines precision the power operator
*/
#define real_pow powf

/*
* Defines the highest value for the real number.
*/
#define REAL_MAX FLT_MAX

/*
* Defines the the precision of the absolute magnitude operator.
*/
#define real_abs fabsf

