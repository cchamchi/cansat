/*
CanSat A0_Servo Example

This example sketch shows how to rotate Servo motor with variable Resister
If you tunr the variable Resister the Servo will be rotated

The Cansat board package is required to run this sketch. 
If you have not already done so you can install it from the Arduino IDE board Manager.
For more Information, visit https://github.com/cchamchi/cansat

Steps:
1. connect servo motor to DTLM0 of cansat
2. connect variable resister to ATLM0
for more details refer to http://cansat.kaist.ac.kr/bbs/board.php?bo_table=menu04_05_01&wr_id=7
   this example is Lab 5.
*/


#include <Servo.h>

int varResisterPins=0;
Servo myServo;

void setup() {
  //attach servo ro DTLM0:
  myServo.attach(D0);
  //variable Resister set up as input
  pinMode(varResisterPins,INPUT);
  //Serial monitor;
  Serial.begin(9600);
}

void loop() {
  int value;
  int angle;
  // Read varResister
  value=analogRead(varResisterPins);
  
  //print Resister value to Serial monitor
  Serial.print("Resister value is\t");
  Serial.println(value);

  //mapping Resister value(0~1023) to servo angle(0~180)
  angle=map(value,0,1023,0,180);
  
  // rotate the servo
  myServo.write(angle);
  
  //wait until to rotate the servo motor
  delay(50);
  

}
