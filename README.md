# Low-Pass-Filter

Simple low pass filter based on sampling theory.  This library allows the user to specify a Filter Bandwidth in Hertz and a Sampling Rate in seconds.

##Synopsis

Return RC low-pass filter output samples, given input samples, time interval dt, and time constant RC. From sampling theory:

	RC = 1 / (2 * π * BW)
	α = dt / (RC + dt)
	y[0] := x[0]
	for i from 1 to n
		y[i] = α * x[i] + (1-α) * y[i-1]

Refactoring

	for i from 1 to n
		y[i] = y[i-1] + α * (x[i] - y[i-1])

Rewriting

	NextValue = LastValue + α * (CurrentValue - LastValue)
	LastValue = NextValue
	
The new output will approach the input in ~ 5 RCTime constants. 

For example: With a specified bandwidth of 10 Hz, and a step input applied, the output will settle to the step input value in ~0.08 seconds. 10 Hz is the 3dB point of the filter, where input changes at a rate greater than this frequency begins to roll off at 20 dB per decade (10 Hz, 100Hz, 1000Hz,...) or 6dB per octave (10Hz, 20Hz, 40Hz, 80Hz...)

![alt tag](https://cloud.githubusercontent.com/assets/3778024/21202816/901c5764-c215-11e6-9895-a39fdd9bd3f0.png)

Thanks https://en.wikipedia.org/wiki/Roll-off

##API
	// Specify a LPF based off bandWidth, or as fixed alpha.
	LPF ( double bandWidthInHzOrAlpha, bool isInBandwidth, uint8_t cascades = 1 );

	// Reset filter output to initialValue
	void Reset ( float initialValue =  0.0 );

	// Return last value from the filter.
	float GetLastValue ( void );

	// Get next value from the filter based on the input (current) value
	float NextValue ( float currentValue );
  
## Tests

The example sketch uses the Serial Plotter functionality to display two examples. The first example plots the response of the LPF to a pulse input. This demonstrates the impulse response (risetime/falltime) of the LPF based on the BANDWIDTH_HZ parameter. Risetime / falltime is ~ 0.35 / BANDWIDTH_HZ.  The second example plots the response of the LPF to an input containing multiple sine wave signals and 'noise'. 

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.


