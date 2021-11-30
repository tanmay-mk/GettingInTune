
#include <sinx.h>
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdint.h"
#include "assert.h"

#define TRIG_TABLE_STEPS 	(32)
#define TRIG_TABLE_STEP_SIZE (HALF_PI/TRIG_TABLE_STEPS)

static const int16_t sin_lookup[TRIG_TABLE_STEPS+1] =
  {0, 100, 200, 299, 397, 495, 591, 686, 780, 871, 960, 1047,
   1132, 1214, 1292, 1368, 1440, 1509, 1575, 1636, 1694, 1747,
   1797, 1842, 1882, 1918, 1949, 1976, 1998, 2015, 2027, 2035,
   2037};


int32_t fp_sin(int32_t x)
{
  int32_t idx;
  int sign = 1;

  // If x < -PI, add 2*PI repeatedly until -PI <= x <= PI
  while (x < -PI)
    x += TWO_PI;

  // If x > PI, subtract 2*PI repeatedly until -PI <= x <= PI
  while (x > PI)
    x -= TWO_PI;

  assert(-PI <= x && x <= PI);

  // Fold the range [-PI, 0] into [0, PI]
  if (x < 0) {
    x = -x;
    sign = -1;
  }

  // Fold the range (HALF_PI, PI] into the range [0, HALF_PI]
  if (x > HALF_PI) {
	  x = PI - x;
  }

//  assert(0 <= x && x <= HALF_PI);

  idx = TRIG_TABLE_STEPS * x / HALF_PI;
  int32_t x1 = idx * TRIG_TABLE_STEP_SIZE;

  // exact match: no interpolation needed
  if (x1 == x)
    return sign * sin_lookup[idx];

  // else, interpolate
  int32_t x2 = (idx+1) * TRIG_TABLE_STEP_SIZE;
  int32_t interp = interpolate(x, x1, sin_lookup[idx], x2, sin_lookup[idx+1]);

  return sign * interp;
}

int32_t fp_radians(int val)
{
  return val * PI / 180;
}

int32_t interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
  return ( (((x2 - x1)/2) + ((x - x1) * (y2 - y1))) / (x2 - x1) + y1);
}
