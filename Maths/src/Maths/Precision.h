#pragma once
#include "Core.h"
#include <math.h>

/*
*	Defines a real number, makes it easy to change from single to double precision
*/
typedef float real;

/*
*	Defines precision of the square root operator
*/
#define real_sqrt sqrtf

/*
*	Defines precision the power operator
*/
#define real_pow powf

/*
*	Defines the highest value for the real number.
*/
#define REAL_MAX FLT_MAX

/*
*	Defines the the precision of the absolute magnitude operator.
*/
#define real_abs fabsf

/*
*	Defines precision of the sine operator.
*/
#define real_sin sinf

/*
*	Defines precision of the cosinus operator.
*/
#define real_cos cosf

/*
*	Defines precision of the exponent operator.
*/
#define real_exp expf

/*
*	defines the number e
*/
#define real_epsilon FLT_EPSILON