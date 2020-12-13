#define ENABLE_SIMULATION
#define ENABLE_MOTORS

//#define MODE_SAME // mode: motors vibration at same frequency
//#define MODE_CLOCKWISE // mode: motors vibrate clockwise
//#define MODE_CCLKWISE // mode: motors vibration cclkwise
#define MODE_PLANARDIRECTION // mode: planar direction
//#define MODE_SPATIALDIRECTION // mode: spatial direction

// parameters *****************************************
// mode 1
#ifdef MODE_SAME
int freqLevel = 2; // 1~5, vibration frequency = 1/(0.01*freqLevel)
double ampLevel = 0.5; // 0.0~1.0
#endif

// mode 2
#ifdef MODE_CLOCKWISE
int freqLevel = 2; // 1~5, vibration frequency = 1/(0.01*freqLevel)
double ampLevel = 0.5; // 0.0~1.0
int rollLevel = 5; // 1~5, rolling speed
#endif

// mode 3
#ifdef MODE_CCLKWISE
int freqLevel = 2; // 1~5, vibration frequency = 1/(0.01*freqLevel)
double ampLevel = 0.5; // 0.0~1.0
int rollLevel = 5; // 1~5, rolling speed
#endif

// mode 4
#ifdef MODE_PLANARDIRECTION
int freqLevel = 2; // 1~5, vibration frequency = 1/(0.01*freqLevel)
double ampLevel = 0.5; // 0.0~1.0
int rollLevel = 5; // 1~5, rolling speed
int motorPinDir = 5; // 1~5, direction
#endif

// mode 5
#ifdef MODE_SPATIALDIRECTION
#endif

// ****************************************************

int motorPin1;
int motorPin2;
int motorPin3;
int motorPin4;
int motorPin5;

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

}

// Helper functions **********************************
// 1.0 Serial output
void serialOut(int outMode, int outVal2, double outVal3, int outVal4, int outVal5){
  Serial.print(outMode);
  Serial.print(' ');
  Serial.print(outVal2);
  Serial.print(' ');
  Serial.print(outVal3, 4);
  Serial.print(' ');
  Serial.print(outVal4);
  Serial.print(' ');
  Serial.println(outVal5);
}

// 2.1 only fire one motor
void fireOne(int freqLevel, double ampLevel, int rollLevel, int motorPinFire, int outMode, int motorPinDir){
  for(int i=0; i<(255*ampLevel); i++){
    for(int j=0; j<freqLevel; j++){
      #ifdef ENABLE_MOTORS
      analogWrite(motorPinFire, i);
      #endif
      delay(5);
      #ifdef ENABLE_SIMULATION
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir);
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
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir);
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
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir);
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
      serialOut(outMode, freqLevel, ampLevel, rollLevel, motorPinDir);
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
void vibSame(int freqLevel, double ampLevel){
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
      serialOut(1, freqLevel, ampLevel, -1, -1);
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
      serialOut(1, freqLevel, ampLevel, -1, -1);
      #endif
    }
  }
}
// ****************************************************

// Mode 2: vibration clockwise ********************************
void vibClockwise(int freqLevel, double ampLevel, int rollLevel){
  fireOne(freqLevel, ampLevel, rollLevel, motorPin1, 2, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin2, 2, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin3, 2, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin4, 2, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin5, 2, -1);
}
// ****************************************************

// Mode 3: vibration counterclockwise *************************
void vibCclkwise(int freqLevel, double ampLevel, int rollLevel){
  fireOne(freqLevel, ampLevel, rollLevel, motorPin5, 3, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin4, 3, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin3, 3, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin2, 3, -1);
  fireOne(freqLevel, ampLevel, rollLevel, motorPin1, 3, -1);
}
// ****************************************************

// Mode 4: vibration direction to a motor *********************
void vibPlanarDir(int freqLevel, double ampLevel, int rollLevel, int motorPinDir){
  fireTwo(freqLevel, ampLevel, rollLevel, (motorPinDir+2)%5, (motorPinDir-2+5)%5, 4, motorPinDir);
  fireTwo(freqLevel, ampLevel, rollLevel, (motorPinDir+1)%5, (motorPinDir-1+5)%5, 4, motorPinDir);
  fireOne(freqLevel, ampLevel, rollLevel, motorPinDir, 4, motorPinDir);
}
// ****************************************************

void loop() {
  
  #ifdef MODE_SAME
  //freqLevel: vibration frequency = 1/(0.01*freqLevel)
  vibSame(freqLevel, ampLevel);
  #endif

  #ifdef MODE_CLOCKWISE
  vibClockwise(freqLevel, ampLevel, rollLevel);
  #endif

  #ifdef MODE_CCLKWISE
  vibCclkwise(freqLevel, ampLevel, rollLevel);
  #endif

  #ifdef MODE_PLANARDIRECTION
  vibPlanarDir(freqLevel, ampLevel, rollLevel, motorPinDir);
  #endif

  
}
