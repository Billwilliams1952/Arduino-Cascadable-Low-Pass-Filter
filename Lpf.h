/*
 * Lpf.h
 * 
 * Copyright 2016 Bill Williams <wlwilliams1952@gmail.com, github/BillWilliams1952>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef __LPF_H__

#define __LPF_H__

#include <Arduino.h>

class LPF {
	// Return RC low-pass filter output samples, given input samples, time interval dt, and time constant RC
	//    α = dt / (RC + dt) where RC = 1 / (2 * π * BW)
	//    y[0] := x[0]
	//    for i from 1 to n
	//       y[i] = α * x[i] + (1-α) * y[i-1]
	//    return y

	// Or refactoring
	//    for i from 1 to n
	//       y[i] = y[i-1] + α * (x[i] - y[i-1])

	public:

	// Specify a LPF based off bandWidth and sampleTime
	LPF ( float bandWidthInHz, float sampleTimeInSec, float initialValue =  0.0 );

	// Simple case where you just want a filter without worring about
	// sample rates or bandwidths.
	LPF ( float alpha, float initialValue =  0.0 );

	// Reset filter output to initialValue
	void Reset ( float initialValue =  0.0 );

	// Return last value from the filter.
	float GetLastValue ( void );

	// Get next value from the filter based on the input (current) value
	float NextValue ( float currentValue );

	// Use for AGC and other responses where the sample time changes.
	float NextValue ( float currentValue, float sampleTimeInSec );
	
	private:

	float RCTime, alpha, lastValue;
};

#endif


