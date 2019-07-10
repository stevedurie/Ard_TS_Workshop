int interval=1000; // the time we need to wait
int previousMillis=0; // millis() returns an unsigned long.
bool ledState = false; // state variable for the LED

int interval2=300; // the time we need to wait
int previousMillis2=0; // millis() returns an unsigned long.
bool ledState2 = false; // state variable for the LED

int interval3=5000; // the time we need to wait
int previousMillis3=0; // millis() returns an unsigned long.
bool ledState3 = false; // state variable for the LED

void setup() {
  //millis = 0;
 pinMode(2, OUTPUT);
 digitalWrite(2, ledState);

 pinMode(3, OUTPUT);
 digitalWrite(4, ledState2);

 pinMode(4, OUTPUT);
 digitalWrite(4, ledState3);
}
 
void loop() {
 int currentMillis = millis(); // grab current time

 

 if ( (currentMillis - previousMillis) >= interval) {
  
   ledState = !ledState; // "toggles" the state
   digitalWrite(2, ledState); // sets the LED based on ledState
   // save the "current" time
   previousMillis = millis();
 }

 if ( (currentMillis - previousMillis2) >= interval2) {
  
   ledState2 = !ledState2; // "toggles" the state
   digitalWrite(3, ledState2); // sets the LED based on ledState
   // save the "current" time
   previousMillis2 = millis();
 }

  if ( (currentMillis - previousMillis3) >= interval3) {
  
   ledState3 = !ledState3; // "toggles" the state
   digitalWrite(4, ledState3); // sets the LED based on ledState
   // save the "current" time
   previousMillis3 = millis();
 }





 
}
