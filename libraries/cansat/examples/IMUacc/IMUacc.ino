
#include <CansatDebug.h>
#include <CansatIMU.h>
#include <CansatSystem.h>
#include <CansatBT.h>

void setup() {

  // put your setup code here, to run once:
  CansatSystemInit();  
  cansatIMU.begin(115200);
  cansatBT.begin();

  while(!cansatBT.isConnected()){
    cansatBT.sendln("BT connected");
    cansatBT.sendln("Welcome to Cansat");
  }
 
}

float gyroacc[6]; //[roll,pirch,yaw,x,y,z]
void loop() {
  // put your main code here, to run repeatedly:

  if(cansatIMU.read(gyroacc)){      

   float acc,x,y,z;
   x=gyroacc[3];
   y=gyroacc[4];
   z=gyroacc[5];
  
   acc=pow( (x*x+y*y+z*z),0.5);     
   Serial.println(acc);

  }
    delay(20);
    
}

