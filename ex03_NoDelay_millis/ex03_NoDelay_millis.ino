int interval=100; // the time we need to wait
int previousMillis=0; // millis() returns an unsigned long.
bool ledState = false; // state variable for the LED

//int interval2=300; // the time we need to wait
//int previousMillis2=0; // millis() returns an unsigned long.
//bool ledState2 = false; // state variable for the LED
//
//int interval3=5000; // the time we need to wait
//int previousMillis3=0; // millis() returns an unsigned long.
//bool ledState3 = false; // state variable for the LED

int pins[] = { 2, 3, 4, 5, 6};
int pinsR[] = { 7, 8, 9, 10, 11};
int pinplay[] = { 2, 3, 4, 5};

bool lstates[] = { false,false,false,false,false};

int ledCount = 0;

void setup() {
  //millis = 0;

  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(lstates[i], ledState);

  }

}
 
void loop() {
 int currentMillis = millis(); // grab current time

 if ( (currentMillis - previousMillis) >= interval) {
  
   lstates[ledCount] = !lstates[ledCount]; // "toggles" the state
   
   digitalWrite(pins[ledCount], lstates[ledCount]); // sets the LED based on ledState
   // save the "current" time
   
   if ( lstates[ledCount] == false) {
    ledCount++;
   }

   if (ledCount > sizeof(lstates)-1 ) {
     ledCount= 0;
   }
   previousMillis = millis();
   
 }


 if ( (currentMillis - previousMillis2) >= interval2) {
  
   lstates[ledCount] = !lstates[ledCount]; // "toggles" the state
   
   digitalWrite(pins[ledCount], lstates[ledCount]); // sets the LED based on ledState
   // save the "current" time
   
   if ( lstates[ledCount] == false) {
    ledCount++;
   }

   if (ledCount > sizeof(lstates)-1 ) {
     ledCount= 0;
   }
   previousMillis = millis();
   
 }

 
 
}
