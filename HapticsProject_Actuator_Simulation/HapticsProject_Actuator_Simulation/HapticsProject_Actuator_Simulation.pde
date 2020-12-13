/* HapticsProject Simulation 
Yihao Liu
Modified from the .pde file from the Haptics course 2020Fall
by Prof. Jeremy Brown. Original code source:
 Based on the Arduining example which is based on the Tom Igoe example.
 Mofified by Cara Nunez 5/1/2019:
*/

import processing.serial.*;

Serial myPort;        // The serial port

// parsing mode identifier
float inMode=0; // 1: MODE_SAME
float inModeLast=0;

// parsing parameter
float inVal2 = 0;
float inVal2Last = 0;
float inVal3 = 0;
float inVal3Last = 0;
float inVal4 = 0;
float inVal4Last = 0;
float inVal5 = 0;
float inVal5Last = 0;

// graphical motor size
int motorSize = 30;

// vib amp
int vib11=0; int vib12=0;
int vib21=0; int vib22=0;
int vib31=0; int vib32=0;
int vib41=0; int vib42=0;
int vib51=0; int vib52=0;

// mode parameters
float freqLevel = inVal2;
float ampLevel = inVal3;
float rollLevel = inVal4;
float motorPinDir = inVal5;
int counter = 0;

void setup () {
  size(600, 400);        
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[3], 74880); 
  myPort.bufferUntil('\n');
  background(0);      // set inital background:
}

// vibrate motor at given amp
void drawEllipse(float ampLevel, int freqLevel, boolean mot1, boolean mot2, boolean mot3, boolean mot4, boolean mot5){
  // random direction
  float r1 = random(-1.0,1.0);
  float r2 = random(-1.0,1.0);
  float r = sqrt(r1*r1+r2*r2);
  r1 = r1/r; r2 = r2/r;
  for(int i=0; i<freqLevel*70; i++){
    if(mot1){vib11 = (int)(ampLevel*10.0*r1); vib12 = (int)(ampLevel*10.0*r2);}
    else{vib11 = 0; vib12 = 0;}
    if(mot2){vib21 = (int)(ampLevel*10.0*r2); vib22 = (int)(ampLevel*10.0*r1);}
    else{vib21 = 0; vib22 = 0;}
    if(mot3){vib31 = (int)(ampLevel*10.0*r1); vib32 = (int)(ampLevel*10.0*r2);}
    else{vib31 = 0; vib32 = 0;}
    if(mot4){vib41 = (int)(ampLevel*10.0*r2); vib42 = (int)(ampLevel*10.0*r1);}
    else{vib41 = 0; vib42 = 0;}
    if(mot5){vib51 = (int)(ampLevel*10.0*r1); vib52 = (int)(ampLevel*10.0*r2);}
    else{vib51 = 0; vib52 = 0;}
    ellipse(186+vib11,163+vib12,motorSize,motorSize);
    ellipse(229+vib21,297+vib22,motorSize,motorSize);
    ellipse(371+vib31,297+vib32,motorSize,motorSize);
    ellipse(414+vib41,163+vib42,motorSize,motorSize);
    ellipse(300+vib51,80+vib52,motorSize,motorSize);
  }
}

void draw () {
  
  background(0); 
  
  stroke(255,0,0);     //stroke color
  strokeWeight(2);        //stroke wider
  noFill();
  circle(300,200,240);
  stroke(0,255,0);     //stroke color
  fill(0,255,0);
  // plot the 5 motors (planar directionality)
  switch((int)inMode){
    
    case 1: // MODE_SAME
      freqLevel = inVal2;
      ampLevel = inVal3;
      drawEllipse(ampLevel, (int)freqLevel, true, true, true, true, true);
      break;
      
    case 2: // MODE_CLOCKWISE
      freqLevel = inVal2;
      ampLevel = inVal3;
      rollLevel = inVal4;
      if(counter%(5*2*rollLevel)>=0 && counter%(5*2*rollLevel)<2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, false, false, false, true);
      if(counter%(5*2*rollLevel)>=2*rollLevel && counter%(5*2*rollLevel)<2*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, false, false, true, false);
      if(counter%(5*2*rollLevel)>=2*2*rollLevel && counter%(5*2*rollLevel)<3*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, false, true, false, false);
      if(counter%(5*2*rollLevel)>=3*2*rollLevel && counter%(5*2*rollLevel)<4*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, true, false, false, false);
      if(counter%(5*2*rollLevel)>=4*2*rollLevel && counter%(5*2*rollLevel)<5*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, true, false, false, false, false);
      counter++;
      if(counter == 5*5*2*rollLevel)
        counter = 0;
      break;
      
    case 3: // MODE_CCLKWISE
      freqLevel = inVal2;
      ampLevel = inVal3;
      rollLevel = inVal4;
      if(counter%(5*2*rollLevel)>=0 && counter%(5*2*rollLevel)<2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, true, false, false, false, false);
      if(counter%(5*2*rollLevel)>=2*rollLevel && counter%(5*2*rollLevel)<2*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, true, false, false, false);
      if(counter%(5*2*rollLevel)>=2*2*rollLevel && counter%(5*2*rollLevel)<3*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, false, true, false, false);
      if(counter%(5*2*rollLevel)>=3*2*rollLevel && counter%(5*2*rollLevel)<4*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, false, false, true, false);
      if(counter%(5*2*rollLevel)>=4*2*rollLevel && counter%(5*2*rollLevel)<5*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, false, false, false, false, true);
      counter++;
      if(counter == 5*5*2*rollLevel)
        counter = 0;
      break;
      
    case 4: // MODE_PLANARDIRECTION
      freqLevel = inVal2;
      ampLevel = inVal3;
      rollLevel = inVal4;
      motorPinDir = inVal5;
      if(counter%(3*2*rollLevel)>=0 && counter%(3*2*rollLevel)<2*rollLevel){
        drawEllipse(ampLevel, (int)freqLevel, 
          ((motorPinDir+2)%5)==1 || ((motorPinDir-2+5)%5)==1, 
          ((motorPinDir+2)%5)==2 || ((motorPinDir-2+5)%5)==2, 
          ((motorPinDir+2)%5)==3 || ((motorPinDir-2+5)%5)==3, 
          ((motorPinDir+2)%5)==4 || ((motorPinDir-2+5)%5)==4, 
          ((motorPinDir+2)%5)==0 || ((motorPinDir-2+5)%5)==0);
      }
      if(counter%(3*2*rollLevel)>=2*rollLevel && counter%(3*2*rollLevel)<2*2*rollLevel){
        drawEllipse(ampLevel, (int)freqLevel, 
          ((motorPinDir+1)%5)==1 || ((motorPinDir-1+5)%5)==1,
          ((motorPinDir+1)%5)==2 || ((motorPinDir-1+5)%5)==2,
          ((motorPinDir+1)%5)==3 || ((motorPinDir-1+5)%5)==3,
          ((motorPinDir+1)%5)==4 || ((motorPinDir-1+5)%5)==4,
          ((motorPinDir+1)%5)==0 || ((motorPinDir-1+5)%5)==0);
      }
      if(counter%(3*2*rollLevel)>=2*2*rollLevel && counter%(3*2*rollLevel)<3*2*rollLevel)
        drawEllipse(ampLevel, (int)freqLevel, 
          motorPinDir==1,
          motorPinDir==2, 
          motorPinDir==3, 
          motorPinDir==4, 
          motorPinDir==5);
      counter++;
      if(counter == 3*3*2*rollLevel)
        counter = 0;
      break;
    default:
  }
  
}

void serialEvent (Serial myPort) {
  
  // serial parsing
  String val = myPort.readStringUntil('\n');
  // skip serial async error (null error)
  try {
    String val1 = split(val, ' ')[0].trim();
    String val2 = split(val, ' ')[1].trim();
    String val3 = split(val, ' ')[2].trim();
    String val4 = split(val, ' ')[3].trim();
    String val5 = split(val, ' ')[4].trim();
    inMode = float(val1);
    inVal2 = float(val2);
    inVal3 = float(val3);
    inVal4 = float(val4);
    inVal5 = float(val5);
  } catch (Exception e) {
  }
  
  // validity check
  if(Float.isNaN(inMode) || 
      Float.isNaN(inVal2) || 
      Float.isNaN(inVal3) || 
      Float.isNaN(inVal4) || 
      Float.isNaN(inVal5)){
    inMode = inModeLast;
    inVal2 = inVal2Last;
    inVal3 = inVal3Last;
    inVal4 = inVal4Last;
    inVal5 = inVal5Last;
  }
  
  // value loop update
  inModeLast = inMode;
  inVal2Last = inVal2;
  inVal3Last = inVal3;
  inVal4Last = inVal4;
  inVal5Last = inVal5;
}
