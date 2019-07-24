
// This version includes btn triggered behaviors as well as a 'sleep' sequence
// Based on the ESP32 logic so the led pwms works differenly. see ledcAnalogWrite at the bottom
// Also again notice there is a simple ledbuffer, which provides a more robust way of controlling the 
// leds given different behaviours one can use.

#include <TaskScheduler.h>

// which Device/Box are we coding for? Each box should be labeled on the back.
byte deviceNum = 2;

const byte rledPin1 = 12;  //A11  Red
const byte gledPin2 = 27; //A10   Grn
const byte bledPin3 = 33; //A9    Blu

const int buttonPin1 = 32; //A7 button
const int buttonPin2 = 14; //A6 button
const int buttonPin3 = 4;  //A5 button
const int buttonPin4 = 36; //A4 button

boolean buttonState1 = 0;
boolean buttonState2 = 0;
boolean buttonState3 = 0;
boolean buttonState4 = 0;

int led_buffer[3] = {0, 0, 0};

int led_logic[4][3] = {{255, 0, 0},
                       {0, 255, 0},
                       {0, 0, 255},
                       {255, 0, 255}
};

// btn logic for all devices (boxes). Where 1 is normally open , and 0 is normally closed.
boolean btn_logic[4][4] = {{1, 1, 1, 1},  //box 1 btn logic
                           {0, 0, 0, 1},  //box 2 btn logic
                           {1, 1, 1, 1},  //box 3 btn logic
                           {1, 1, 0, 1}}; //box 4 btn logic


//sleep vars
bool sleepState = true;
int lumi = 0;
int fadeAmount1 = 0;
bool dirUp1 = true;


// Callback methods prototypes
void btnCb();
void ledCb();
void sleepCb();
void sleepBhvCb();

//Tasks
Task btnTask(20, TASK_FOREVER, &btnCb);
Task ledTask(30, TASK_FOREVER, &ledCb);
Task sleepTimeTask(1000, 20, &sleepCb);
Task sleepBhvTask(100, TASK_FOREVER, &sleepBhvCb);

Scheduler runner;

void setup () {
  Serial.begin(115200);
  Serial.println("Scheduler TEST");

  // Remember the its device number -1 , i.e. Box 2 is 1, etc
  // as we are adjusting for array being 0-based
  deviceNum = deviceNum - 1;

  ledcAttachPin(rledPin1, 1); // assign RGB led pins to channels
  ledcAttachPin(gledPin2, 2);
  ledcAttachPin(bledPin3, 3);

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);

  runner.init();
  Serial.println("Initialized scheduler");

  runner.addTask(ledTask);
  runner.addTask(btnTask);
  runner.addTask(sleepTimeTask);
  runner.addTask(sleepBhvTask);
  ledTask.enable();
  btnTask.enable();
 // sleepTimeTask.enable();
  sleepBhvTask.enable();

  Serial.println("tasks added and enabled");

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
}
void loop () {
  runner.execute();
}


////////////////// Tasks ////////////////////



void btnCb() {
  
  // starting with all being reset unless we are in sleep state
   
  if (!sleepState) {
  led_buffer[0] = 0;
  led_buffer[1] = 0;
  led_buffer[2] = 0;
  }

  Serial.print("t1: --- ");
 
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == btn_logic[deviceNum][0]) {
   // Serial.println("11111111 is PRESSED--");
    led_buffer[0] = 255;  // red on
  }


  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 == btn_logic[deviceNum][1]) {
   // Serial.println(" 22222222 is PRESSED--");
    led_buffer[1] = 255; // grn on
  }


  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 == btn_logic[deviceNum][2]) {
   // Serial.println(" 3333333 is PRESSED--");
    led_buffer[2] = 255;  // blu on
  }

  buttonState4 = digitalRead(buttonPin4);
  if (buttonState4 == btn_logic[deviceNum][3]) {
   // Serial.println(" 444444 is PRESSED--");
    led_buffer[0] = 255;  // red and blu on to make purple
    led_buffer[2] = 255;
  }

}

// this does nothing but update what is the simple ledbuffer.
void ledCb() {
  //Serial.println("update led: --- ");
    //uint32_t duty = (8191 / 255) * min(0, 255);
  
  ledcWrite(1, led_buffer[0]);
  ledcWrite(2, led_buffer[1]);
  ledcWrite(3, led_buffer[2]);

}

void sleepCb() {


}

void sleepBhvCb(){

//  bounce code
  if (dirUp1 == true) {
    fadeAmount1+= 5;
    if (fadeAmount1 > 255 )  {
       fadeAmount1 = 255;
       dirUp1 = false;
    }
    
  } else {
    
    fadeAmount1-= 5;
    if (fadeAmount1 < 0 )  {
       fadeAmount1 = 0;
       dirUp1 = true;
    }
    
  }
   
//  Serial.println(fadeAmount1);

   led_buffer[0] = fadeAmount1;
   led_buffer[1] = 255-fadeAmount1;
   led_buffer[2] = fadeAmount1;

 }

 

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  // write duty to LEDC
  ledcWrite(channel, duty);
}
