/*
CanSat cds Example

This example sketch shows how cds sensor works
If you tunr on the light then cds value be small and LED turns ON

The Cansat board package is required to run this sketch. 
If you have not already done so you can install it from the Arduino IDE board Manager.
For more Information, visit https://github.com/cchamchi/cansat

Steps:
1. set the sw1/sw2 to left side(in front view) to connect cds with analoginput 
2. Compile and upload the sketch.
*/

#define cds1 5  //analog pin 5
#define cds2 6  //analog pin 6 near SD card

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //turn all LEDs OFF
  pinMode(LED0, OUTPUT);
  digitalWrite(LED0,HIGH);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1,HIGH);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2,HIGH);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value,i;
  value=analogRead(cds1);
  Serial.print("cds1 value=");
  Serial.println(value);
  if(value<250)digitalWrite(LED0,LOW); //LED on
  else digitalWrite(LED0,HIGH); //LED off

  value=analogRead(cds2);
  Serial.print("cds2 value=");
  Serial.println(value);
  if(value<250)digitalWrite(LED3,LOW);
  else digitalWrite(LED3,HIGH);  
  
  delay(500);
     

}
