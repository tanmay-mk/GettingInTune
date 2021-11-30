/*
 * PES Assignment 7
 *
 * File Name: sinx.c
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */

/* 	LIBRARY FILES	*/
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"
#include "assert.h"

/* 	OTHER FILES TO BE INCLUDED	*/
#include "sinx.h"

/* 	MACROS	*/
#define TRIG_TABLE_STEPS 			32
#define TRIG_TABLE_STEP_SIZE 		HALF_PI/TRIG_TABLE_STEPS

/* 	GLOBAL VARIABLES	*/
static const int16_t sin_lookup[TRIG_TABLE_STEPS+1] =
  {0, 100, 200, 299, 397, 495, 591, 686, 780, 871, 960, 1047,
   1132, 1214, 1292, 1368, 1440, 1509, 1575, 1636, 1694, 1747,
   1797, 1842, 1882, 1918, 1949, 1976, 1998, 2015, 2027, 2035,
   2037};

/*
 * @brief: see documentation in sinx.h
 */
int32_t sinx(int32_t value)
{
  int32_t index;
  int sign = 1;

  // If x < -PI, add 2*PI repeatedly until -PI <= x <= PI
  while (value < -PI)
  {
	  value += TWO_PI;
  }

  // If x > PI, subtract 2*PI repeatedly until -PI <= x <= PI
  while (value > PI)
  {
	  value -= TWO_PI;
  }

  assert(-PI <= value && value <= PI);

  // Fold the range [-PI, 0] into [0, PI]
  if (value < 0)
  {
	value = -value;
    sign = -1;
  }

  // Fold the range (HALF_PI, PI] into the range [0, HALF_PI]
  if (value > HALF_PI)
  {
	  value = PI - value;
  }

  index = TRIG_TABLE_STEPS * value / HALF_PI;
  int32_t x1 = index * TRIG_TABLE_STEP_SIZE;

  // exact match: no interpolation needed
  if (x1 == value)
    return sign * sin_lookup[index];

  // else, interpolate
  int32_t x2 = (index+1) * TRIG_TABLE_STEP_SIZE;
  int32_t interp = interpolate(value, x1, sin_lookup[index], x2, sin_lookup[index+1]);

  return sign * interp;
}

/*
 * @brief: see documentation in sinx.h
 */
int32_t interpolate(int32_t value, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
  return ( (((x2 - x1)/2) + ((value - x1) * (y2 - y1))) / (x2 - x1) + y1);
}
