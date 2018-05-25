#include <CansatSystem.h>
#include <CansatSerial.h>
#include <CansatGPS.h>

void setup() {
  // put your setup code here, to run once:
  CansatSystemInit();  
  Serial.begin(115200);
  cansatGPS.begin(9600);
  Serial.println("Cansat GPS test");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(cansatGPS.read()){  
       Serial.print("date=");
       Serial.println(cansatGPS.date());
       Serial.print("time=");
       Serial.println(cansatGPS.time()/100.);
       Serial.print("lat=");
       Serial.println((cansatGPS.location().lat* 1.0e-7f),7);
       Serial.print("lon=");
       Serial.println((cansatGPS.location().lng* 1.0e-7f),7);       
       Serial.print("altitude(m)=");
       Serial.println(cansatGPS.location().alt/100.); 
       Serial.print("num_sat=");
       Serial.println(cansatGPS.num_sats()); 
       Serial.print("speed(km/s)=");
       Serial.println(cansatGPS.ground_speed_km());
       Serial.print("cource=");
       Serial.println(cansatGPS.ground_course());
       Serial.println("*********************************");    
  
  }
  
  

}
