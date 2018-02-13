// CANSAT 2016  LED BLINK //
// Added LED3
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED0 as an output.
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED0, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

  digitalWrite(LED2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

  digitalWrite(LED3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED3, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

}
