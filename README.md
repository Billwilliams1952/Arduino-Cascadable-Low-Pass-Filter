# Low-Pass-Filter
Simple low pass filter

##Synopsis

##API

	LPF ( float bandWidthInHz, float sampleTimeInSec );

	LPF ( float alpha );

	float GetLastValue ( void );
	
	float NextValue ( float currentValue );

	float NextValue ( float currentValue, float sampleTimeInSec );
  
##License


