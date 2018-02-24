/*
CanSat LED blink Example

This example sketch shows how LED turn on/off

The Cansat board package is required to run this sketch. 
If you have not already done so you can install it from the Arduino IDE board Manager.
For more Information, visit https://github.com/cchamchi/cansat

*/
void setup() {
  // initialize digital pin LEDs as an output.
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}


void loop() {
  digitalWrite(LED0, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED0, LOW);    // turn the LED on by making the voltage LOW
  delay(500);              // wait for a second

  digitalWrite(LED1, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED on by making the voltage LOW
  delay(500);              // wait for a second

  digitalWrite(LED2, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED2, LOW);    // turn the LED on by making the voltage LOW
  delay(500);              // wait for a second

  digitalWrite(LED3, HIGH);   // turn the LED off (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED3, LOW);    // turn the LED on by making the voltage LOW
  delay(500);              // wait for a second

}
