// by Jenner Hanni
// http://github.com/wicker
//
// Based on code from Bruce Allen 
// http://playground.arduino.cc/mMain/MaxSonar
//
// Based on code from Tone example
// https://www.arduino.cc/en/Tutorial/ToneMelody?from=Tutorial.Tone

#include "pitches.h"

int noteArray[15];

const int pwPin = 2;

long pulse, inches, cm;
int outOctave, count;

void setup() {
  count = 0;
  
  noteArray[9]  = NOTE_C1;
  noteArray[10] = NOTE_C2;
  noteArray[11] = NOTE_C3;
  noteArray[12] = NOTE_C4;
  noteArray[13] = NOTE_C5;
  noteArray[14] = NOTE_C6;

  Serial.begin(9600);
  Serial.println("Begin.");
  pinMode(pwPin, INPUT);

}

void loop() {
  
  pulse = pulseIn(pwPin, HIGH);
  inches = pulse/147;
  Serial.println(inches);
  cm = inches * 2.54;
  
  if (inches <= 8) {
    outOctave = 10;
  }
  else if (inches >= 19) {
    outOctave = 120;
  }
  else {
    outOctave =  inches;
    tone(3,noteArray[inches],1000/8);
    Serial.println(outOctave);
  }
//  Serial.print("1, ");
//  Serial.print(count);
//  Serial.print(", Note_on_c, 11, ");
//  Serial.print(outOctave);
//  Serial.println(", 127");
//  
//  if (count > 2000)
//  {
//    Serial.print("1, ");
//    Serial.print(count + 50);
//    Serial.println(", End_track");
//    Serial.println("0, 0, End_of_file");
//    return;
//  }
//  count = count + 100;
  }
