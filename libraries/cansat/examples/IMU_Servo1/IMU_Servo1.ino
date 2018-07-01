/*
  CanSat IMU_Servo1 Example
  
  This example sketch shows how to control Servo motor with IMU
  The servo will face to same direction regardless of cansat rotation
  
  The Cansat board package is required to run this sketch. 
  If you have not already done so you can install it from the Arduino IDE board Manager.
  For more Information, visit https://github.com/cchamchi/cansat
  
  Steps:
  1. connect 2axis servo motor to DTLM0-horizontal servo/DTLM1-vertical servo 
  for more details refer to http://cansat.kaist.ac.kr/bbs/board.php?bo_table=menu04_05_01&wr_id=7
     this example is Lab 4.
  */

#include <CansatDebug.h>
#include <CansatIMU.h>
#include <CansatSystem.h>
#include <Servo.h>

Servo hServo;
Servo vServo;


void setup() {
  // cansat initialization
  CansatSystemInit();  
  // cansat IMU init. baud rate must be 115200
  cansatIMU.begin(115200);
  // attach servos
  //DTLM0-horizontal servo/DTLM1-vertical servo 
  hServo.attach(D0);
  vServo.attach(D1);  
  Serial.begin(115200);
}

void loop() {
  float gyro[6]; //[roll,pirch,yaw,x_acc,y_acc_z_acc]
  int vAngle,hAngle;
  
  //read IMU values [roll,pirch,yaw]  
  if(cansatIMU.read(gyro,3){
    Serial.print("gyro roll/yaw\t");      
    Serial.print(gyro[0]);
    Serial.print('\t');
    Serial.println(gyro[2]);

    // roll value control vertical servo
    // servo range is 0~180 degree, so keep 90 degree as refernce position
    // if roll is zero, it means x axis' rotation angle of cansat is zero 
    // then vAngle is 90 degree which means vertical servo stand up and face to front
    // if roll is negative value, it means cansat rotate to face down
    // then vAgnle will be below 90 degree and rotate backward
    // which means vertical servo keep to face to front regardless of cansat roll rotation
    vAngle=gyro[0]+90;  // 90 is vertical offset for servo 
    // yaw value control horizontal servo
    hAngle=gyro[2]+90;  // 90 is horizontal offset for servo 

    vServo.write(vAngle);
    hServo.write(hAngle);
  }
  

}
