//Created by Joshua Yaacoub, 2023
//NOTES
//Made for interfacing with a TB6600 stepper motor driver to drive a nema 17 stepper motor
//Using delayMicroseconds() for now, may update to micros() in the future for multitasking
//Contains a variety of functions which can be used with the 2 pin connections from the arduino to the driver, mostly by manipulating the pulse pin (PUL_PIN)
  
  //Interface pins
  const int DIR_PIN = 3;
  const int PUL_PIN = 4;

  //Motor gear reduction and microstepping information
  const int ratio = 28;
  const int steps = 1600; 
  const int stepsPRev = ratio*steps;

  //Used for moveTo function
  int absPos = 0;


  void setup() {
    pinMode(DIR_PIN,OUTPUT);
    pinMode(PUL_PIN,OUTPUT);
    Serial.begin(9600);
  }

//Basic - move the motor a number of steps
  void move(int steps, int dT){
    for(int x=0;x<steps;x++){
      digitalWrite(PUL_PIN,HIGH);
      delayMicroseconds(dT);
      digitalWrite(PUL_PIN,LOW);
    }
  }

//Oscillate by a number of steps and speeds in both directions
  void osc(int steps1, int dT1, int steps2, int dT2){
    digitalWrite(DIR_PIN,HIGH);
    move(steps1,dT1);
    digitalWrite(DIR_PIN,LOW);
    move(steps2,dT2);  

  }

//Quadratic acceleration function for smooth acceleration
  void quadAcc(int totalSteps, int dT1, int dT2){
    int halfsteps = totalSteps/2;
    int r = dT1-dT2;
    int dT;

    for(double x=0;x<0.5;x = x + 1.0/totalSteps){
      dT = -1*r*(pow(1.414*x,2)) + dT2 + r;
      digitalWrite(PUL_PIN,HIGH);
      delayMicroseconds(dT) ;
      digitalWrite(PUL_PIN,LOW);
      
    }
    for(double x=0.5;x<1;x+= 1.0/totalSteps){
      dT = r*(pow(1.414*(x-1),2)) + dT2;
      digitalWrite(PUL_PIN,HIGH);
      delayMicroseconds(dT);
      digitalWrite(PUL_PIN,LOW);
      
    }
  }

//Linear Acceleration (lerp) function for acceleration
  void linAcc(int totalSteps, int dT1, int dT2){
    int dT;
    float divFac = totalSteps;
    for(int x=0;x<totalSteps;x++){
      dT = dT1 + (dT2-dT1)*(x/divFac);
      digitalWrite(PUL_PIN,HIGH);
      delayMicroseconds(dT);
      digitalWrite(PUL_PIN,LOW);
    }

  }

//Enable motor (holding torque)
  void lock(){
    digitalWrite(PUL_PIN,HIGH);
  }

//Disable motor
  void unlock(){
    digitalWrite(PUL_PIN,LOW);
  }


//Move the motor a predefined angle
  void moveAngle(double angle, int dT){
    for(int x=0;x<(stepsPRev * (angle/360.0)); x++){
      digitalWrite(PUL_PIN,HIGH);
      delayMicroseconds(dT);
      digitalWrite(PUL_PIN,LOW);      
  }
}

//Move the motor to a target position
void moveTo(int target, int mdT){
  target*=16;
  for(int x=0;x<abs(target-absPos)-32;x++){
      digitalWrite(PUL_PIN,HIGH);
      if(abs(target-absPos) < 200 && abs(target-absPos) > 100){
        delayMicroseconds(mdT*2);
      }

      else if(abs(target-absPos) < 100 && abs(target-absPos) > 50){
        delayMicroseconds(mdT*3);
      }

      else if(abs(target-absPos) < 50 && abs(target-absPos) > 0){
        delayMicroseconds(mdT*4);
      }

      else{
        delayMicroseconds(mdT);
      }
      
      digitalWrite(PUL_PIN,LOW);
      if(target>absPos){
        absPos++;
        digitalWrite(DIR_PIN,HIGH);
        
      }
      if(target<absPos){
        absPos--;
        digitalWrite(DIR_PIN,LOW);
      }
    }
}


  //Place commands here
  void run(){
    //Example moveTo function, using a potentiometer as input on pin A1
    moveTo(analogRead(A1),100);
  }






  void loop() {
    run();
  }
