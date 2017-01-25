
/*
 * LPF_Test_Suite.ino
 * 2017 WLWilliams
 * 
 * This sketch demonstrates the use of the LPF library. Use the Serial Plotter under Tools to
 * see the effects of a single or casscaded LPF on the inputs.
 * 
 * This program is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version. 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of
 * the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Library originally added December 2016 by Bill Williams
 *
 * This example code is in the public domain.
 * 
 * https://github.com/Billwilliams1952/Low-Pass-Filter
 */

#include <Lpf.h>

#define PULSE_OUT         10          // Your arduino pin
#define ANALOG_IN         A0          // Your arduino pin

#define BANDWIDTH_HZ          1       // 3-dB bandwidth of the filter
#define SAMPLE_TIME_SEC       10e-3   // Expected sample time
#define SIGNAL_FREQUENCY_HZ   0.3     // Our test input signal frequency

/*
 * Create a Low Pass Filter - it's default initialization is 0.0.  To change it, 
 * call Reset with an initialValue.
 */
LPF lpf(BANDWIDTH_HZ,SAMPLE_TIME_SEC);      
/*
 * If you concatentate LPF's with the same parameters, you increase its rolloff by another
 * 20dB / decade or 6 dB per octave
 */
LPF lpf2(BANDWIDTH_HZ,SAMPLE_TIME_SEC);           

void setup() {
    Serial.begin(115200);

    while (!Serial) ;

    pinMode(PULSE_OUT,OUTPUT);
    digitalWrite(PULSE_OUT,HIGH);
    pinMode(ANALOG_IN,INPUT);
}

void loop() {
    
    digitalWrite(13,millis()%1000 > 500);   // I'm alive blinker

    /*
     * Uncomment the test you wish to visualize
     */
     
    PlotRisetimeResponse();

    //PlotSineWaveWithNoiseResponse();

    delay(SAMPLE_TIME_SEC*1000);
}

/*
 * Plot filter response to ac signals using serial plotter
 */
void PlotSineWaveWithNoiseResponse ( void ) {
  
    static unsigned int dt = 0;
    float inputSignal, twoPiDt = 2.0 * PI * dt * SAMPLE_TIME_SEC;

    inputSignal = 5.0 * sin(SIGNAL_FREQUENCY_HZ * twoPiDt) + 
                  /* now add some higher order signals to filter out */
                  2.0 * sin(BANDWIDTH_HZ * 10 * twoPiDt) +
                  1.0 * sin(BANDWIDTH_HZ * 20 * twoPiDt) +
                  /* some 'noise' */ (float)random(-100, 100) / 100.0;
    dt++;

    /* 
     *  Plot input signal
     */
    Serial.print(inputSignal);   Serial.print(" ");
    /* 
     * Plot output of first LPF. The amplitude of frequencies above BANDWIDTH_HZ
     * begin to roll off at 20dB per decade or 6 dB per octave
     */
    float outlpf1 = lpf.NextValue(inputSignal);
    Serial.print(outlpf1);
    Serial.print(" ");
    /* 
     * Plot output of second LPF. The amplitude of frequencies above BANDWIDTH_HZ
     * begin to roll off at 40dB per decade or 12 dB per octave
     */
    Serial.println(lpf2.NextValue(outlpf1));
}

/*
 * Plot risetime / falltime using serial plotter
 */
void PlotRisetimeResponse ( void ) {

    static unsigned long timer = millis();
    static float lpfInput = 5.0;
    unsigned long PW_MSEC = 1000.0 / (SIGNAL_FREQUENCY_HZ * 2.0);

    /* Allow the input to pulse */
    if ( (millis() - timer) >= PW_MSEC ) {
        digitalWrite(PULSE_OUT,!digitalRead(PULSE_OUT));
        lpfInput = 5.0 * (float)analogRead(ANALOG_IN) / 1024.0;
        timer = millis();
    }
            
    /* 
     *  Plot input signal
     */
    Serial.print(lpfInput);
    Serial.print(" "); 
    /*
     * Plot impulse response output of LPF (it's risetime / falltime).
     * This is equal to ~ 0.35 / BANDWIDTH_HZ.
     */
    float val = lpf.NextValue(lpfInput);
    Serial.println(val);
}



