
#ifndef SINX_H_
#define SINX_H_


#include <stdint.h>

#define TRIG_SCALE_FACTOR	(2037)
#define HALF_PI				(3200)
#define PI 					(6399)
#define TWO_PI				(12799)

int32_t fp_sin(int32_t x);

int32_t interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

int32_t convert_to_radians(int val);

#endif /* SINX_H_ */
