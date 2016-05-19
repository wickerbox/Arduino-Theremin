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

// these arrays contain each key's set of notes
int noteArray_A[9];
int noteArray_C[15];
int noteArray_F[15];

// huge array to hold the current tune
// largest note in pitches.h is 4978
// 2^16 = 
uint16_t current_tune[1024];
uint16_t curr_key;
uint16_t note_delay; // in milliseconds

// set up state
uint8_t state = START;

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
      delay(1000);
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, LOW);
      delay(1000);
      break;
    case RECORD:
      digitalWrite(recordLEDPin, HIGH);
      digitalWrite(playbackLEDPin, LOW);
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
