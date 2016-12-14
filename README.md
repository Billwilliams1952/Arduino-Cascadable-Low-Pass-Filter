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
	
The new output will approach the input (within 1 %) in ~ 5 RCTime. So for a specified bandwidth of 10 Hz, with a step input applied, the output will settle to within 1% in ~0.08 seconds. The 10 Hz is the 3dB point of the filter, where input changes at a rate greater than this frequency begins to roll off at 20 dB per decade or 6dB per octave. ![alt tag](https://cloud.githubusercontent.com/assets/3778024/21202816/901c5764-c215-11e6-9895-a39fdd9bd3f0.png)

Thanks https://en.wikipedia.org/wiki/Roll-off

##API
	/* Create instance given a bandwidth and sampletime*/
	LPF ( float bandWidthInHz, float sampleTimeInSec );

	/* Create instance using a value of alpha */
	LPF ( float alpha );

	/* Return the last value from the LPF */
	float GetLastValue ( void );
	
	/* Return the next value from the LPF */
	float NextValue ( float currentValue );

	/* Return the next value from the LPF given a new sampletime */
	float NextValue ( float currentValue, float sampleTimeInSec );
  
## Tests

Use the **TBD** example sketch to verify correct operation. 

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.


