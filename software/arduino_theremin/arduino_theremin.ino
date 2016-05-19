// by Jenner Hanni
// http://github.com/wicker
//
// Based on code from Bruce Allen 
// http://playground.arduino.cc/mMain/MaxSonar
//
// Based on code from Tone example
// https://www.arduino.cc/en/Tutorial/ToneMelody?from=Tutorial.Tone
//
// Using the readCapacitivePin function from Mario Becker, Alan Chatham, and others
// http://playground.arduino.cc/Code/CapacitiveSensor

#include "pitches.h"

#define START    0
#define RECORD   1
#define HOLD     2
#define PLAYBACK 3

#define A 0
#define C 1
#define F 2

#define MAXNOTE  7
#define MAXTUNECOUNT 299

// set up state
uint8_t state = START;
uint8_t last_state = START;

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
uint16_t current_tune[300];
uint16_t current_tune_count = 0;
uint16_t total_current_notes = 0;
uint16_t curr_key = A;
uint16_t note_delay = 50; // in milliseconds
uint16_t note = 0;

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

uint8_t readCapacitivePin(int pinToMeasure) {

  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  uint8_t SREG_old = SREG; //back up the AVR Status Register
  // Prevent the timer IRQ from disturbing our measurement
  noInterrupts();
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
  if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // End of timing-critical section; turn interrupts back on if they were on before, or leave them off if they were off before
  SREG = SREG_old;

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  return cycles;
}

void startupBlinkLEDs() {
  digitalWrite(recordLEDPin, HIGH);
  digitalWrite(playbackLEDPin, HIGH);
  delay(200);
  digitalWrite(recordLEDPin, LOW);
  digitalWrite(playbackLEDPin, LOW);
  delay(200);
  digitalWrite(recordLEDPin, HIGH);
  digitalWrite(playbackLEDPin, HIGH);
  delay(200);
  digitalWrite(recordLEDPin, LOW);
  digitalWrite(playbackLEDPin, LOW);
  delay(200);      
}

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
      startupBlinkLEDs();
      break;
    case RECORD:

      // if we just entered the record state, clear the current tune
      if (last_state != RECORD) {
        for (current_tune_count = 0; current_tune_count < MAXTUNECOUNT; current_tune_count++)
          current_tune[current_tune_count] = 0;
        current_tune_count = 0;
      }
      
      digitalWrite(recordLEDPin, HIGH);
      digitalWrite(playbackLEDPin, LOW);

      // get note
      pulse = pulseIn(pwmPin, HIGH);
      note = pulse/147;
      if (note > 14)
        note = 14;
      else if (note < 7)
        note = 7;
      note = note - 7;

      // record the note in the correct key
      if (current_tune_count < 299) 
        if (curr_key == A)
          current_tune[current_tune_count++] = noteArray_A[note];
        else if (curr_key == C)
          current_tune[current_tune_count++] = noteArray_C[note];
        else 
          current_tune[current_tune_count++] = noteArray_F[note];

      // play note in correct key
      if (curr_key == A)
        tone(3,noteArray_A[note],1000/8);
      else if (curr_key == C)
        tone(3,noteArray_C[note],1000/8);
      else 
        tone(3,noteArray_F[note],1000/8);

      delay(note_delay);

      break;
    case HOLD:
      // if we just came here from record, let's capture the number of
      // notes in our current tune, in case we want to play it back
      if (last_state == RECORD) {
        total_current_notes = current_tune_count - 1;
      }
      
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, LOW);

      delay(note_delay);

      break;
    case PLAYBACK:
      // reset the counter so we can play it back once
      // use the 
      if (last_state != PLAYBACK) {
        current_tune_count = 0;
      }
      if (current_tune_count <= total_current_notes) {
        tone(3,current_tune[current_tune_count],1000/8);
        current_tune_count++;
      }
      digitalWrite(recordLEDPin, LOW);
      digitalWrite(playbackLEDPin, HIGH);

      delay(note_delay*2);

      break;
  }


  // change the key based on cap sense input
  if (readCapacitivePin(aKeyPin) > 5)
    curr_key = A;
  else if (readCapacitivePin(cKeyPin) > 5)
    curr_key = C;
  else if (readCapacitivePin(fKeyPin) > 5)
    curr_key = F;
  else
    curr_key = curr_key;

  // change state based on input switch
  last_state = state;
  if (digitalRead(recordPin) == HIGH)
    state = RECORD;
  else if (digitalRead(playbackPin) == HIGH)
    state = PLAYBACK;
  else 
    state = HOLD;
    
}
