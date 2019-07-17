// This is a simple version of using a neoPixel strip with TS.
// Note the important use of the arrays (redAr,grnAr, bluAr) to create a buffer
// that all hardware fuctions call from. There are no direct calls the neoPixels
// but only calls form the arrays to create a 'pixel buffer'.

#include <TaskScheduler.h>
#include <Adafruit_NeoPixel.h>

// NeoPixel input pin
#define PIN  6

// number of of neopixel in the device?
#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void mainCb();
void redCb();
void grnCb();
void bluCb();

// Defining each task with its speed or how oftern it triggers [interval] in milliseconds, 
// the number of repeats [iterations], which can be a number of use TASK_FOREVER for no limit.
// and the callback function to call for each cycle [&NameOfFunction]
// i.e. nameOfTask(interval,iterations,&NameOfFunction)

Task tMain(5, TASK_FOREVER, &mainCb);
Task tR(100, TASK_FOREVER, &redCb);
Task tG(250, TASK_FOREVER, &grnCb);
Task tB(500, TASK_FOREVER, &bluCb);

/* A simple data buffer for the leds to keep track
  of each pixel and its RGB values.M
  ake sure the NUMPIXELS match the numbers the array
*/

int redAr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};
int grnAr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};
int bluAr[] = {0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0};

// current color
int mainRed =   0;
int mainGreen = 0;
int mainBlue =  0;

// the starting values for the counters for each task
int mainCounter = 0;
int redCounter = 0;
int grnCounter = 0;
int bluCounter = NUMPIXELS - 1;

//Create main task scheduling object
Scheduler runner;

void setup() {
  
  Serial.begin(115200);
  // Setting up main TS runner object, 
  runner.init();
  Serial.println("Initialized scheduler");

 // adding the tasks to the TS object
  runner.addTask(tMain);
  runner.addTask(tR);
  runner.addTask(tG);
  runner.addTask(tB);
  Serial.println("tasks added");

  
  // turning on or 'enabling' each task
  tMain.enable();
  tR.enable();
  tG.enable();
  tB.enable();
  Serial.println("tasks enabled");

  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.begin(); 
  // Set all pixel colors to 'off'
  pixels.clear(); 
}

void loop() {
  // if using TS then dont put any code in the main loop except
  // for the TS object
  runner.execute();
}

// This main Callback is used to manage the hardware and update it as fast as possible.
// See Task tMain

void mainCb() {

  for ( int i; i < NUMPIXELS; i++) {
    // Update the pixel colors to the hardware, based on the data buffer.
    pixels.setPixelColor(i, pixels.Color(redAr[i], grnAr[i], bluAr[i]));
    pixels.show();
  }

}

// All 3 color call backs are used at different rates depending on what was defined in
// in addition red and grn go up in sequence, while blu goes down.
// See Tasks tR, tG, tB

void redCb() {
  
  // clear red buffer
  for (int i = 0; i < NUMPIXELS; i++) {
    redAr[i] = 0;    // turn the LED off by making the voltage LOW
  }
 
  // reset counter if out of range
  if ( redCounter > NUMPIXELS - 1) {
    redCounter = 0;
  }
  
  // set color to current red led in count
  redAr[redCounter] = 200; // define the value for current red color
  redCounter++; // next led in sequence

}

void grnCb() {
  
  // clear grn buffer
  for (int i = 0; i < NUMPIXELS; i++) {
    grnAr[i] = 0;    // turn the LED off by making the voltage LOW
  }
  
  // reset counter if out of range
  if ( grnCounter > NUMPIXELS - 1) {
    grnCounter = 0;
  }
  
  // set color to current grn led in count
  grnAr[grnCounter] = 200;
  grnCounter++;

}

void bluCb() {
  
  // clear blu buffer
  for (int i = 0; i < NUMPIXELS; i++) {
    bluAr[i] = 0;    // turn the LED off by making the voltage LOW
  }
  
  // reset counter if out of range
  if ( bluCounter < 0 ) {
    bluCounter = NUMPIXELS - 1;
  }

  // set color to current blu led in count
  bluAr[bluCounter] = 200;
  bluCounter--;  // note we are going down in sequence


}
