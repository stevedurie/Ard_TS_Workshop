/*


*/

#include <TaskScheduler.h>
#include "pitches.h"

// differentsolo melody
//int solo[] = { NOTE_A3,NOTE_AS3,NOTE_B3,NOTE_C3,NOTE_CS3,NOTE_D3,NOTE_E3,NOTE_A4};
//
//int soloDurations[] = {2, 3, 1, 2, 4, 2, 3, 3 };

// note durations: 4 = quarter note, 8 = eighth note, etc.:

int solo[] = {  NOTE_DS5, NOTE_C5, NOTE_DS5, NOTE_C6, NOTE_FS5, 0};
int soloDurations[] = { 4, 4, 4, 8, 6, 4 };

int riff[] = { NOTE_F2, NOTE_F2, NOTE_G2, NOTE_F2, NOTE_GS2, NOTE_F2, NOTE_AS2, NOTE_A2 };
int riffDurations[] = { 4, 4, 4, 4, 4, 4, 4, 4};

float transpose[] = {0.5, 1.0, 2, 1.4};

// constants won't change. They're used here to set pin numbers:
const int button1Pin = 4;     // toggle btn
const int button2Pin = 2;     // momentary btn
const int led1Pin =  13;      // this is for led digital out
const int led2Pin =  8;     // this is for led analog out
const int speakPin = 9;    // new position for speaker
const int analogInPin0 = A0;  // Analog input pin for the pot
const int analogInPin1 = A1;  // Analog input pin  for the photocell

int sensorValue0 = 0;        // value read from the pot
int outputValue0 = 0;        // value output after map

int sensorValue1 = 0;        // value read from the photo cell
int outputValue1 = 0;        // valuer output from map

int button1State = 0;         // variable for reading toggle btn
int button2State = 0;         // variable for reading the momentary btn

int whichT = 0;

int soloNote = 0;
int riffNote = 0;

// TaskScheduler Callback methods (or prototypes)
// Every callback needs to have this prototype at the top like this

void sensorCB();
void mainCB();
void soloCB();
void soloRestCB();
void riffCB();
void riffRestCB();

/*TaskScheduler Behaviors Defined*/
//sensor runs every 20 milliseoncds indefinitely, every cycle it triggers the cb function t1Callback
// NOTE: put the '&' infront of any callback functions.
Task sensor(20, TASK_FOREVER, &sensorCB);
////mainloop runs every 80 milliseconds indefinitely, calls mainCB
Task mainloop(80, TASK_FOREVER, &mainCB);
////fade runs every 90 milliseconds seconds 300 times calls fadeCB
Task soloz(30, TASK_FOREVER, &soloCB);
//// 1 second task forever
Task riffz(30, TASK_FOREVER, &riffCB);

//Create main task scheduling object
Scheduler runner;

void setup() {

  Serial.begin(115200);
  Serial.println("Scheduler TEST");

  // initialize the led pin as an output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  Serial.println("Initialized scheduler");

  // add these tasks to the scheduler
  runner.addTask(sensor);
  runner.addTask(mainloop);
  runner.addTask(soloz);
  runner.addTask(riffz);

  // start them up
  sensor.enable();
  mainloop.enable();
  // did not enable solo or riff as we will control that with a switch


}

void loop () {
  runner.execute();
}


void sensorCB() {
  // read the btn pins
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // read the pot and read the photocell
  sensorValue0 = analogRead(analogInPin0);
  sensorValue1 = analogRead(analogInPin1);

  // map it to the range of the analog out for the pot
  outputValue0 = map(sensorValue0, 0, 1023, 0, 255);

  // map it to the range of the analog out for the photcell
  outputValue1 = map(sensorValue1, 0, 900, 255, 0);

  // change the inputput values:
  //    Serial.print("digital1 -- > ");
  //    Serial.print(button1State);
  //    Serial.print(" ");
  //    Serial.print(" digital2 --> ");
  //    Serial.print(button2State);
  //    Serial.print(" ");
  //    Serial.print("analog1 -- > ");
  //    Serial.print(sensorValue0);
  //    Serial.print(" ");
  //    Serial.print(outputValue0);
  //    Serial.print(" analog2 --> ");
  //    Serial.print(sensorValue1);
  //    Serial.print(" ");
  //    Serial.println(outputValue1);

}

void mainCB() {

  if ( button1State == HIGH) {

    //  Serial.println("ON");

    if (button2State == HIGH) {
      Serial.println("btn2----");
      //soloz.restart();
      soloz.enableIfNot();   
      riffz.disable();
     // riffz.restart();

    } else {
      riffz.enableIfNot();   
      soloz.disable();
    //  soloz.restart();
    }

  } else {
    riffz.disable();
    soloz.disable();
  }



}


void soloCB() {

  Serial.println("solo play-- > ");
  if ( soloz.isFirstIteration() ) {
    Serial.println("first and traspose-- > ");
    // pick a transpose value;
    whichT = int(random(4));
    soloNote = 0;
  }

  int noteDuration = 1000 / soloDurations[soloNote];
  tone(speakPin, solo[soloNote]*transpose[whichT], constrain(noteDuration * (outputValue1 * .02) , 1, 500) );
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = constrain( noteDuration * (outputValue1 * .02) * 1.1, 1, 500);

  // toggle the led
  digitalWrite(led1Pin, !digitalRead(led1Pin));
  //}

  if ( soloNote > 7  ) {
    soloNote = 0;
  } else {
    soloNote++;
  }
  soloz.setCallback(&soloRestCB);
  soloz.delay(pauseBetweenNotes);
}

void soloRestCB() {
  noTone(speakPin);
  soloz.setCallback(&soloCB);
}


void riffCB() {

  Serial.println("riff play-- > ");
  if ( riffz.isFirstIteration() ) {
    Serial.println("first and traspose-- > ");
    // pick a transpose value;
    whichT = int(random(4));
    riffNote = 0;
  }

  int noteDuration = 1000 / riffDurations[riffNote];
  tone(speakPin, riff[riffNote]*transpose[whichT], constrain(noteDuration * (outputValue0 * .02) , 1, 500) );
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = constrain( noteDuration * (outputValue0 * .02) * 1.1, 1, 500);

  // toggle the led
  digitalWrite(led1Pin, !digitalRead(led1Pin));
  //}

  if ( riffNote > 7  ) {
     riffNote = 0;
     whichT = int(random(4));
  } else {
    riffNote++;
    riffz.setCallback(&riffRestCB);
    riffz.delay(pauseBetweenNotes);
  }
  
   
}

void riffRestCB() {
  
  noTone(speakPin);
  riffz.setCallback(&riffCB);
}
