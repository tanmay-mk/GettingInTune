/*
 * PES Assignment 7
 *
 * File Name: sinx.h
 *
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 *
 */
#ifndef _SINX_H_
#define _SINX_H_

/* 	LIBRARY FILES	*/
#include <stdint.h>

/* 	MACROS	*/
#define TRIG_SCALE_FACTOR	2037
#define HALF_PI				3200	//(3.1415/2)*2037
#define PI 					6399	//(3.1415)*2037
#define TWO_PI				12799	//(2*3.1415)*2037

/* 	FUNCTION PROTOTYPES	*/
/* -----------------------------------------------------------------
 * @brief		: 	Sine function - calculates the trigonometric sine
 * 					value.
 *
 * @parameters	: 	x: the value of which the sine is to be calculated
 *
 * @returns		: 	sine of x
 --------------------------------------------------------------------*/
int32_t sinx(int32_t value);

/* -----------------------------------------------------------------
 * @brief		: 	Interpolation function - if the argument of x does
 * 					not belong in the lookup table, then interpolation
 * 					is used.
 *
 * @parameters	: 	x		: the value of which the sine is to be calculated
 * 					x1, x2	: x coordinate of the value used for interpolation
 * 					y1, y2	: y coordinate of the value used for interpolation
 *
 * @returns		: 	interpolated value
 --------------------------------------------------------------------*/
int32_t interpolate(int32_t value, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif /* _SINX_H_ */
