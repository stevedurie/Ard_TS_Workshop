
// Simple Box Test Program to verify hardware and buttons are working
// This just activates a color based on one of 4 buttons being pressed.
// note below there is a logic table for each buttons depending on device.
// As some buttons have inverted logic.
// This is also based on the ESP32 logic so the led pwm fuction works differenly than a Arduino.
// see ledcAnalogWrite at the bottom

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
boolean btn_logic[4][4] = {{1, 1, 1, 1}, //box 1 btn logic
  {0, 0, 0, 1}, //box 2 btn logic
  {1, 1, 1, 1}, //box 3 btn logic
  {1, 1, 0, 1}
}; //box 4 btn logic


// Callback methods prototypes

void ledCb();
void btnCb();

//Tasks
Task ledTask(50, TASK_FOREVER, &ledCb);
Task btnTask(75, TASK_FOREVER, &btnCb);

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
  ledTask.enable();
  btnTask.enable();


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

void ledCb() {
  Serial.println("update led: --- ");
  //int val = 255;

  //uint32_t duty = (8191 / 255) * min(0, 255);

  ledcWrite(1, led_buffer[0]);
  ledcWrite(2, led_buffer[1]);
  ledcWrite(3, led_buffer[2]);

}

void btnCb() {

  // starting with all being reset
  led_buffer[0] = 0;
  led_buffer[1] = 0;
  led_buffer[2] = 0;

  Serial.print("t1: --- ");
  //  Serial.println(millis());

  buttonState1 = digitalRead(buttonPin1);
  Serial.print("Btn1 - ");
  Serial.println(buttonState1);
  if (buttonState1 == btn_logic[deviceNum][0]) {
    Serial.println("11111111 is PRESSED--");
    led_buffer[0] = 255;  // red on
  }


  buttonState2 = digitalRead(buttonPin2);
  Serial.print("Btn2 -- ");
  Serial.println(buttonState2);
  if (buttonState2 == btn_logic[deviceNum][1]) {
    Serial.println(" 22222222 is PRESSED--");
    led_buffer[1] = 255; // grn on
  }


  buttonState3 = digitalRead(buttonPin3);
  Serial.print("Btn3 -- ");
  Serial.println(buttonState3);
  if (buttonState3 == btn_logic[deviceNum][2]) {
    Serial.println(" 3333333 is PRESSED--");
    led_buffer[2] = 255;  // blu on
  }

  buttonState4 = digitalRead(buttonPin4);
  Serial.print("Btn4  -");
  Serial.println(buttonState4);
  if (buttonState4 == btn_logic[deviceNum][3]) {
    Serial.println(" 444444 is PRESSED--");
    led_buffer[0] = 255;  // red and blu on to make purple
    led_buffer[2] = 255;
  }

}

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  // write duty to LEDC
  ledcWrite(channel, duty);
}
