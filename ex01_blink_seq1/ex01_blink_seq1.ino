/*
 
*/
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;
int pin5 = 6;
//int pinX = 11;

int del = 50;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);

  //pinMode(pinX, INPUT);
  
    
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pin1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(del);                       // wait for a second
  digitalWrite(pin1, LOW);    // turn the LED off by making the voltage LOW
  delay(del);     
   digitalWrite(pin2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(del);                       // wait for a second
  digitalWrite(pin2, LOW);    // turn the LED off by making the voltage LOW
  delay(del);     
   digitalWrite(pin3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(del*-);                       // wait for a second
  digitalWrite(pin3, LOW);    // turn the LED off by making the voltage LOW
  delay(del);     
   digitalWrite(pin4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(del);                       // wait for a second
  digitalWrite(pin4, LOW);    // turn the LED off by making the voltage LOW
  delay(del);     
   digitalWrite(pin5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(del);                       // wait for a second
  digitalWrite(pin5, LOW);    // turn the LED off by making the voltage LOW
  delay(del);     
  // wait for a second
}
