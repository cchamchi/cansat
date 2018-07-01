
#include <CansatDebug.h>
#include <CansatIMU.h>
#include <CansatSystem.h>

//#define OUTPUT_PROCESSING
#define OUTPUT_SERIAL_MONITOR



void setup() {

  // put your setup code here, to run once:
  CansatSystemInit();  
  cansatIMU.begin(115200);

  Serial.begin(115200);
 
}

float gyro[6]; //[roll,pirch,yaw,x_acc,y_acc_z_acc]
void loop() {
  // put your main code here, to run repeatedly:

  if(cansatIMU.read(gyro,3)){ // read 3 items

  
   #ifdef OUTPUT_SERIAL_MONITOR   
      Serial.print("gyro roll/pitch/yaw\t");      
      Serial.print(gyro[0]);
      Serial.print('\t');
      Serial.print(gyro[1]);
      Serial.print('\t');
      Serial.println(gyro[2]);
   #endif   
   #ifdef OUTPUT_PROCESSING        
      Serial.print(gyro[0]); //roll,phi
      Serial.print(" ");
      Serial.print(gyro[1]); //pitch,theta
      Serial.print(" ");
      Serial.println(gyro[2]); //yaw,psi
   #endif    
  }   
    
}

