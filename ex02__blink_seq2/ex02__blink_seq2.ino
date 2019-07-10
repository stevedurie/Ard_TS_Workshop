/*
  
*/
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;
int pin5 = 6;
//int pinX = 11;

int del = 50;

int pins[] = { 2, 3, 4, 5, 6};
int pinplay[] = { 2,   3, 4,    5,   6,  5,   4,  3,  2, 1};
int dels[] =    { 150, 150, 150, 150, 150, 150, 150, 150,150, 150};



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }

  //pinMode(pinX, INPUT);
  
    
}

// the loop function runs over and over again forever
void loop() {

  // listen to knob about speeding up or slowing down ghe delays
  
  for (int i = 0; i < sizeof(pinplay); i++) {
    digitalWrite(pinplay[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(dels[i]);                       // wait for a second
    digitalWrite(pinplay[i], LOW);    // turn the LED off by making the voltage LOW
    delay(dels[i]);     
  }

  
  // wait for a second
}
