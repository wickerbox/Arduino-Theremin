// by Jenner Hanni
// http://github.com/wicker
//
// Based on code from Bruce Allen 
// http://playground.arduino.cc/mMain/MaxSonar
//
// Based on code from Tone example
// https://www.arduino.cc/en/Tutorial/ToneMelody?from=Tutorial.Tone

#include "pitches.h"

#define START    0
#define RECORD   1
#define HOLD     2
#define PLAYBACK 3

#define MAXNOTE  7

// set up state
uint8_t state = START;

// these arrays contain each key's set of notes
int noteArray_A[8] = {NOTE_A1,NOTE_A2,NOTE_A3,NOTE_A4,NOTE_A5,
                      NOTE_A6,NOTE_A7};
int noteArray_C[8] = {NOTE_C1,NOTE_C2,NOTE_C3,NOTE_C4,NOTE_C5,
                      NOTE_C6,NOTE_C7};
int noteArray_F[8] = {NOTE_F1,NOTE_F2,NOTE_F3,NOTE_F4,NOTE_F5,
                      NOTE_F6,NOTE_F7};

// huge array to hold the current tune
// largest note in pitches.h is 4978
// 2^16 = 65536
uint16_t current_tune[1024];
uint16_t curr_key;
uint16_t note_delay; // in milliseconds

// inputs
const uint8_t recordPin = 8;
const uint8_t playbackPin = 9;
const uint8_t pwmPin = 2;
const uint8_t aKeyPin = 7;
const uint8_t cKeyPin = 6;
const uint8_t fKeyPin = 5;

// outputs
const uint8_t speakerPin = 3;
const uint8_t playbackLEDPin = A4;
const uint8_t recordLEDPin = A5;

// process input from the rangefinder
long pulse, inches, cm;

// counter variables
int count = 0;
int note = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("Begin.");

  pinMode(recordPin, INPUT);
  pinMode(playbackPin, INPUT);
  pinMode(pwmPin, INPUT);
  pinMode(aKeyPin, INPUT);
  pinMode(cKeyPin, INPUT);
  pinMode(fKeyPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(playbackLEDPin, OUTPUT);
  pinMode(recordLEDPin, OUTPUT);

  state = START;
  
}

void loop() {

  switch(state) {
    case START:
      digitalWrite(recordLEDPin, HIGH);
      digitalWrite(playbackLEDPin, HIGH);
      delay(500);
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, LOW);
      delay(500);
      digitalWrite(recordLEDPin, HIGH);
      digitalWrite(playbackLEDPin, HIGH);
      delay(500);
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, LOW);
      delay(500);      break;
    case RECORD:
      digitalWrite(recordLEDPin, HIGH);
      digitalWrite(playbackLEDPin, LOW);

      for (count = 0; count < MAXNOTE; count++) {
          Serial.print(noteArray_A[count]);
          Serial.print(" ");
      }
      Serial.println(" ");
      for (count = 0; count < MAXNOTE; count++) {
          Serial.print(noteArray_C[count]);
          Serial.print(" ");
      }
      Serial.println(" ");
      for (count = 0; count < MAXNOTE; count++) {
          Serial.print(noteArray_F[count]);
          Serial.print(" ");
      }
      Serial.println(" ");
      
      pulse = pulseIn(pwmPin, HIGH);
      note = pulse/147;
      if (note > 14)
        note = 14;
      else if (note < 7)
        note = 7;
      note = note - 7;
      Serial.println(note);
      delay(1000);
      
      break;
    case HOLD:
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, LOW);
      break;
    case PLAYBACK:
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, HIGH);
      break;
  }

  // change state based on input switch
  if (digitalRead(recordPin) == HIGH)
    state = RECORD;
  else if (digitalRead(playbackPin) == HIGH)
    state = PLAYBACK;
  else 
    state = HOLD;
    
}
