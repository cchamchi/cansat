/*
  CanSat IMU_Servo Example
  
  This example sketch shows how to control Servo motor with IMU
  The servo will mimic the movement of cansat rotation
  
  The Cansat board package is required to run this sketch. 
  If you have not already done so you can install it from the Arduino IDE board Manager.
  For more Information, visit https://github.com/cchamchi/cansat
  
  Steps:
  1. connect 2axis servo motor to DTLM0-horizontal servo/DTLM1-vertical servo 
  for more details refer to http://cansat.kaist.ac.kr/bbs/board.php?bo_table=menu04_05_01&wr_id=7
     
  */

#include <CansatDebug.h>
#include <CansatIMU.h>
#include <CansatSystem.h>
#include <Servo.h>

Servo vServo;
Servo hServo;

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
  float gyro[3]; //[roll,pirch,yaw]  
  int vAngle,hAngle;

  //read IMU values [roll,pirch,yaw]
  cansatIMU.read(gyro);
  Serial.print("gyro roll/yaw\t");      
  Serial.print(gyro[0]);
  Serial.print('\t');
  Serial.println(gyro[2]);
  
  // you can change mapping value for the quick response
  // I mapped roll(-50~50) to vertial angle(20~130)
  vAngle=map(gyro[0],-50,50,20,130);
  // I mapped yaw(-40~40) to horizontal angle(170~10)
  // You have to face to zero yaw direction..may be a south
  // watch the serial monitors yaw value
  hAngle=map(gyro[2],-40,40,170,10);

  vServo.write(vAngle);
  hServo.write(hAngle);
  

}
