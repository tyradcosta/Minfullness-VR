/**************************************************************************
   Textile Game Controllers : Fun with Felting
   Working with Circuit Playground and Conductive Fibers
   This is made to control KidDisco game using Left,Right,Up and Down keys
   http://kiddisco.asmallgame.com/

    This is a small sample to run in the browser to see if your keys are working
   https://editor.p5js.org/2sman/sketches/rkGp1alib
   Arduino Example code:
   https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardwrite/
   https://www.arduino.cc/en/Reference/KeyboardModifiers
   Keyboard Ascii References:
   http://www.asciitable.com/
   Social Body Lab, 2020 Jan.
**************************************************************************/

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#define CAP_THRESHOLD  900//increase this number if unintentional keypresses occur and 
//decrease if buttons aren't sensitive enough
#define DEBOUNCE        100
//chest patch pin
#define  StopPin  A3
//shoulder patch pins
#define  LeftPin A7
#define  RightPin A1
// timer warning tones
#define TONE_FREQ_MIN    523  // C5 note
#define TONE_FREQ_MED    333
#define TONE_FREQ_MAX    988  // B5 note
//timer variables
int p=0;
float total_time = 30000;
float delta_time = total_time / 10;
boolean  timeON = false;
boolean  stopper= false;
boolean capButton(uint8_t pad) {
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) {
    return true;
  } else {
    return false;
  }
}


void setup() {
  // Initialize serial.
  Serial.begin(9600);
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
}

void loop() {
  
  // Check if capacitive touch exceeds threshold on timer stopper. if true then resent the timer.
if (capButton(StopPin)) {
stopper = true; Reset();} 
// if not in contact or stop state then set all leds to off
else{
CircuitPlayground.setPixelColor(0, 0, 0, 0);
CircuitPlayground.setPixelColor(1, 0, 0, 0);
CircuitPlayground.setPixelColor(2, 0, 0, 0);
CircuitPlayground.setPixelColor(3, 0, 0, 0);
CircuitPlayground.setPixelColor(4, 0, 0, 0);
CircuitPlayground.setPixelColor(5, 0, 0, 0);
CircuitPlayground.setPixelColor(6, 0, 0, 0);
CircuitPlayground.setPixelColor(7, 0, 0, 0);
CircuitPlayground.setPixelColor(8, 0, 0, 0);
CircuitPlayground.setPixelColor(9, 0, 0, 0);
CircuitPlayground.setPixelColor(10, 0, 0, 0);
}

//Check if capacitive touch exceeds threshold on shoulder pads. if true start timer. 
if (capButton(LeftPin && RightPin)) {
timeON = true;StartTimer();}
// if not in contact then set all leds to off
else{
CircuitPlayground.setPixelColor(0, 0, 0, 0);
CircuitPlayground.setPixelColor(1, 0, 0, 0);
CircuitPlayground.setPixelColor(2, 0, 0, 0);
CircuitPlayground.setPixelColor(3, 0, 0, 0);
CircuitPlayground.setPixelColor(4, 0, 0, 0);
CircuitPlayground.setPixelColor(5, 0, 0, 0);
CircuitPlayground.setPixelColor(6, 0, 0, 0);
CircuitPlayground.setPixelColor(7, 0, 0, 0);
CircuitPlayground.setPixelColor(8, 0, 0, 0);
CircuitPlayground.setPixelColor(9, 0, 0, 0);
CircuitPlayground.setPixelColor(10, 0, 0, 0);
}



}

//function to reset timer
void Reset() {

timeON = false;
  
Serial.println("Shoulder pad deactivated!");

// turn on the LEDs to make an up arrow for a few flashes
  CircuitPlayground.setPixelColor(0, 255, 0, 0);
  CircuitPlayground.setPixelColor(1, 255, 0, 0);
  CircuitPlayground.setPixelColor(2, 255, 0, 0);
  CircuitPlayground.setPixelColor(7, 255, 0, 0);
  CircuitPlayground.setPixelColor(8, 255, 0, 0);
  CircuitPlayground.setPixelColor(9, 255, 0, 0);
  
//set all leds to off
CircuitPlayground.setPixelColor(0, 0, 0, 0);
CircuitPlayground.setPixelColor(1, 0, 0, 0);
CircuitPlayground.setPixelColor(2, 0, 0, 0);
CircuitPlayground.setPixelColor(3, 0, 0, 0);
CircuitPlayground.setPixelColor(4, 0, 0, 0);
CircuitPlayground.setPixelColor(5, 0, 0, 0);
CircuitPlayground.setPixelColor(6, 0, 0, 0);
CircuitPlayground.setPixelColor(7, 0, 0, 0);
CircuitPlayground.setPixelColor(8, 0, 0, 0);
CircuitPlayground.setPixelColor(9, 0, 0, 0);
CircuitPlayground.setPixelColor(10, 0, 0, 0);
 

//
//play sound
  int frequency = TONE_FREQ_MIN;
  CircuitPlayground.playTone(frequency, 100);

  
  delay(DEBOUNCE);

}

//function to start timer
void StartTimer() {
// for loop counts till 10 using delta time and lights up an LED green for each time it loops through. 
for (p = 0; p < 10; p++) { 
delay(delta_time);
CircuitPlayground.setPixelColor(p, 0, 255, 0);
    Serial.println(p);
    Serial.println("Shoulder pads active!");
// when the loop has cycled through 3 times set led color to yellow
if(p >3){CircuitPlayground.setPixelColor(p, 255, 255, 4);}
//if loop cycles through 6 times set led color to red
if(p >6){CircuitPlayground.setPixelColor(p, 255,0,0);}
//if stop button is pressed reset stop the loop
if(capButton(StopPin)) {break;}

}


}






  


 
