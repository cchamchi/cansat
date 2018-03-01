#include <VC0703.h>
#include <CansatSystem.h>

VC0703 cam = VC0703(&Serial1);
void setup() { 
  CansatSystemInit(); 
  cam.begin(); 
  Serial.begin(38400);
}
void loop() {
  while (Serial.available()) Serial1.write(Serial.read());
  while (Serial1.available()) Serial.write(Serial1.read());
}
