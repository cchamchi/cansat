#include <CansatSystem.h>
#include <CansatBT.h>
void setup() {
  // put your setup code here, to run once:
  CansatSystemInit(); 
  cansatBT.begin();

  while(!cansatBT.isConnected()){
    cansatBT.sendln("BT connected");
    cansatBT.sendln("Welcome to Cansat");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  cansatBT.echo();
  cansatBT.send("Hello world: ");
  cansatBT.sendln((int)millis());
  
  delay(1000);

}
