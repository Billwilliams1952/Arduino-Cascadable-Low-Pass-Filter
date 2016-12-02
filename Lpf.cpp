/*
 * lpf.cpp
 * 
 * Copyright 2016 Bill Williams <wlwilliams1952@gmail.com, github/BillWilliams1952>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General License for more details.
 * 
 * You should have received a copy of the GNU General License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "Lpf.h"

/* Return RC low-pass filter output samples, given input samples,
 * time interval dt, and time constant RC
 * α = dt / (RC + dt) where RC = 1 / (2 * π * BW)
 *     y[0] := x[0]
 *     for i from 1 to n
 *        y[i] = α * x[i] + (1-α) * y[i-1]
 *     return y
 *
 * Or refactoring
 *    for i from 1 to n
 *       y[i] = y[i-1] + α * (x[i] - y[i-1])
 *
 * OR: 	NextValue = LastValue + alpha * (CurrentValue - LastValue)
 * 		LastValue = NextValue
 *
 * The new output will apporach the input in ~ 5 RCTime. So for a
 * specified bandwidth of 10 Hz, with a step input applied, the output
 * will settle in ~0.08 seconds.
 * The 10 Hz is the 3dB point of the filter, where input changes at a
 * rate greater than this frequency begins to roll off at 20 dB per
 * decade or 6dB per octave -- check this??
 *
 */

LPF :: LPF ( float bandWidthInHz, float sampleTimeInSec ) {
	if ( (bandWidthInHz <= 0) || (sampleTimeInSec <= 0) ) {
		RCTime = 0.0;
		alpha = 1.0;
	}
	else {
		RCTime = 1.0 / (TWO_PI * bandWidthInHz);
		alpha = sampleTimeInSec / (RCTime + sampleTimeInSec);
	}
	lastValue = 0.0;
}

/*
 * Simple case where you just want a filter without worring about
 * sample rates or bandwidths
 */
LPF :: LPF ( float alpha ) {
	this->alpha = ((alpha > 0) && (alpha < 1.0)) ? alpha : 1.0;
	RCTime = 0.0;
	lastValue = 0.0;
}

float LPF :: GetLastValue ( void ) {
	return lastValue;
}

float LPF :: NextValue ( float currentValue ) {
	lastValue = lastValue + alpha * (currentValue - lastValue);
	return lastValue;
}

float LPF :: NextValue ( float currentValue, float sampleTimeInSec ) {
	// Use for AGC and other responses where the sample time changes...
	if ( RCTime == 0.0 )		// Declared using alpha - no sampleTime
		return NextValue(currentValue);
	alpha = sampleTimeInSec / (RCTime + sampleTimeInSec);
	lastValue = lastValue + alpha * (currentValue - lastValue);
	return lastValue;
}


