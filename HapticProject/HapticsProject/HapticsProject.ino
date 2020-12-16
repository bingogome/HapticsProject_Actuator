/* *************
 *  This is an integration of the Audio recgnition
 *  and the actuator module.
 *  External libraries required: 
 *  1. arduinoFFT
 *  2. AdafruitBusIO
 *  3. Adafruit VEML 6075
 *  Use Sketch -> include library -> manage libraries
 *  Search for the libraries and install them
*/

#include "arduinoFFT.h"
#include <math.h>

#define ENABLE_SIMULATION
//#define ENABLE_MOTORS

// These mode handlers are not needed for the "HapticsProject.ino" *************
// They are intended only for the HapticsProject_Actuator(_Simulation).ino **********

//#define MODE_SAME // mode: motors vibration at same frequency
//#define MODE_CLOCKWISE // mode: motors vibrate clockwise
//#define MODE_CCLKWISE // mode: motors vibration cclkwise
//#define MODE_PLANARDIRECTION // mode: planar direction
//#define MODE_SPATIALDIRECTION // mode: spatial direction

//******************************************************************************

#define SAMPLES 128             //number of freq bins. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048 // gives sampling period/freq

// parameters *****************************************
int freqLevel = 2; // 1~5, vibration frequency = 1/(0.01*freqLevel)
double ampLevel = 0.5; // 0.0~1.0
int rollLevel = 5; // 1~5, rolling speed
int motorPinDir = 4; // 1~5, direction
// ****************************************************

arduinoFFT FFT = arduinoFFT();

//ARDUINO FFT Need the number of samples, the sampling frequency, 
//and the real and imag components of the samples

unsigned int sample_period; //in us
unsigned long time_us; //need sample period in microseconds for processing

double vReal[SAMPLES]; //real part of samples
double vImag[SAMPLES]; //im part of samples

int motorPin1;
int motorPin2;
int motorPin3;
int motorPin4;
int motorPin5;

double peak_freq = 0.0;

boolean audioRecged = false;

void setup() {

  Serial.begin(74880);
  
  motorPin1 =11;
  motorPin2 =10;
  motorPin3 =9;
  motorPin4 =6;
  motorPin5 =5;
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorPin5, OUTPUT);

  sample_period = round(1e6/SAMPLING_FREQUENCY); //period = 1/f, in us = period * 1e6

}

// Helper functions **********************************
// 1.0 Serial output
void serialOut(int outMode, int outVal2, double outVal3, int outVal4, int outVal5, double outVal6){
  Serial.print(outMode);
  Serial.print(' ');
  Serial.print(outVal2);
  Serial.print(' ');
  Serial.print(outVal3, 4);
  Serial.print(' ');
  Serial.print(outVal4);
  Serial.print(' ');
  Serial.print(outVal5);
  Serial.print(' ');
  Serial.println(outVal6, 2);
}

// 2.1 only fire one motor
void fireOne(int freqLevel, double ampLevel, int rollLevel, int motorPinFire, int outMode, int motorPinDir, double peak_freq){
  for(int i=0; i<(255*ampLevel); i++){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPinFire, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir, peak_freq);
      #endif
    }
  }
  for(int i=(255*ampLevel); i>0; i--){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPinFire, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir, peak_freq);
      #endif
    }
  }
}

// 2.2 only fire two motors
void fireTwo(int freqLevel, double ampLevel, int rollLevel, 
    int motorPinFire1, int motorPinFire2, int outMode, int motorPinDir){
      
  // map to real pin on board
  motorPinFire1 = mapPin(motorPinFire1);
  motorPinFire2 = mapPin(motorPinFire2);
  
  // send signal and serial output
  for(int i=0; i<(255*ampLevel); i++){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPinFire1, i);
      analogWrite(motorPinFire2, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir, -1);
      #endif
    }
  }
  for(int i=(255*ampLevel); i>0; i--){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPinFire1, i);
      analogWrite(motorPinFire2, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir, -1);
      #endif
    }
  }
}

// 3.0 map pin# (1~5) to pin on board(11,10,9,6,5)
int mapPin(int motorPinFire){
  switch(motorPinFire){
    case 1:
      return 11;
      break;
    case 2:
      return 10;
      break;
    case 3:
      return 9;
      break;
    case 4:
      return 6;
      break;
    case 0:
      return 5;
      break;
  }
}
// ****************************************************

// Mode 1: vibration at the same time *************************
// freqLevel: vibration frequency = 1/(0.01*freqLevel)
void vibSame(int freqLevel, double ampLevel, double peak_freq){
  for(int i=0; i<(255*ampLevel); i++){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPin1, i);
      analogWrite(motorPin2, i);
      analogWrite(motorPin3, i);
      analogWrite(motorPin4, i);
      analogWrite(motorPin5, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(1, freqLevel, ampLevel, -1, -1, peak_freq);
      #endif
    }
  }
  for(int i=(255*ampLevel); i>0; i--){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPin1, i);
      analogWrite(motorPin2, i);
      analogWrite(motorPin3, i);
      analogWrite(motorPin4, i);
      analogWrite(motorPin5, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(1, freqLevel, ampLevel, -1, -1, peak_freq);
      #endif
    }
  }
}
// ****************************************************

// Mode 2: vibration clockwise ********************************
void vibClockwise(int freqLevel, double ampLevel, int rollLevel, double peak_freq){
  fireOne(freqLevel, ampLevel, rollLevel, motorPin1, 2, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin2, 2, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin3, 2, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin4, 2, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin5, 2, -1, peak_freq);
}
// ****************************************************

// Mode 3: vibration counterclockwise *************************
void vibCclkwise(int freqLevel, double ampLevel, int rollLevel, double peak_freq){
  fireOne(freqLevel, ampLevel, rollLevel, motorPin5, 3, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin4, 3, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin3, 3, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin2, 3, -1, peak_freq);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin1, 3, -1, peak_freq);
}
// ****************************************************

// Mode 4: vibration direction to a motor - 2D*********************
void vibPlanarDir(int freqLevel, double ampLevel, int rollLevel, int motorPinDir){
  fireTwo(freqLevel, ampLevel, rollLevel, (motorPinDir+2)%5, (motorPinDir-2+5)%5, 4, motorPinDir);
  fireTwo(freqLevel, ampLevel, rollLevel, (motorPinDir+1)%5, (motorPinDir-1+5)%5, 4, motorPinDir);
  fireOne(freqLevel, ampLevel, rollLevel, motorPinDir, 4, motorPinDir, peak_freq);
}
// ****************************************************

// Mode 4: vibration direction to a motor - 3D*********************
void vibSpatialDir(){
  
}
// ****************************************************

// Audio recg. ****************************************

double audioRecg(){
  //SAMPLING
  for(int i = 0; i < SAMPLES; i++)
   {
      
      time_us = micros(); //number of us since the Arduino board began running the current program (timescale)
      vReal[i] = analogRead(A0); //gives real val from A0 pin
      vImag[i] = 0; //sets im term = 0 (real signal)

    //wait time between samples
      while(micros() < (time_us + sample_period))
      {
        //do nothing
      }
   }

  //FFT Processing
   FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //window data to capture relevant freqs
   FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD); //compute FFT on data
   FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);  //gives magnitude of each freq component
  
   //peak freq of signal (for distinguishing signals)
   double peak_freq_picked = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
   return peak_freq_picked;
}

// ****************************************************
void loop() {

  while(peak_freq==0.0){
    peak_freq = audioRecg(); // 400 hz, 700 hz, 1000 hz
  }
  
  // MODE_SAME 400 hz
  if(peak_freq>200.0 && peak_freq<=550.0)
    vibSame(freqLevel, ampLevel, peak_freq);
    
  // MODE_CLOCKWISE 700 hz
  if(peak_freq>550.0 && peak_freq<=850.0)
    vibClockwise(freqLevel, ampLevel, rollLevel, peak_freq);

  // MODE_CCLKWISE 1000 hz
  if(peak_freq>850.0 && peak_freq<=1150.0)
    vibCclkwise(freqLevel, ampLevel, rollLevel, peak_freq);
  
}
