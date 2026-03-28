/*
  Arduino Starter Kit project

  Digital Hourglass with Piezzo and tic-tac LEDs
  ==============================================
  Based on Project 8 - Digital Hourglass example

  Parts required:
  - 10 kilohm resistor
  - eight 220 ohm resistors
  - six red LEDs
  - two green LEDs
  - tilt switch
  - piezzo

  Created 2026-03-25
  by Ondřej Kužel  
*/

// named constant
const int SwitchPin = 8;
const int TicLedPin = 10;
const int TacLedPin = 11;

const int PiezzoPin = 9;

const int NumOfLeds = 6;

// frekvences of tones
const int NoteSec = 262;
const int NoteMin = 349;


// variables
unsigned long previous_time = 0;  // store the last time an LED was updated
unsigned long previous_tic_time = 0; // store the last time of switching of an tic-tac LEDs

int switch_state = 0;             // the current switch state
int prev_switch_state = 0;         // the previous switch state
int tic_tac_led = 10;           // the switched on tic-tac LED (pin)
int led = 2;                     // a variable to refer to the LEDs

// 10000 = 10 seconds in milliseconds
unsigned long interval = 10000;  // interval at which to light the next LED = 10 sec
unsigned long tic_tac_interval = 250; // interval at which switch the tic-tac LEDs on/off

void setup() {
  // set the LED pins as outputs
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(TicLedPin, OUTPUT);
  pinMode(TacLedPin, OUTPUT);

  // set the tilt switch pin as input
  pinMode(SwitchPin, INPUT);

  // Set PiezzoPin as output
  pinMode(PiezzoPin, OUTPUT);
}

void loop() {
  // store the time since the Arduino started running in a variable
  unsigned long current_time = millis();

  // Tic Tac Leds
  if (current_time - previous_tic_time > tic_tac_interval) {
    previous_tic_time = current_time;
    if (tic_tac_led == TicLedPin) {
      digitalWrite(TicLedPin, LOW);
      digitalWrite(TacLedPin, HIGH);
      tic_tac_led = TacLedPin;
    } else if (tic_tac_led == TacLedPin) {
      digitalWrite(TacLedPin, LOW);
      digitalWrite(TicLedPin, HIGH);
      tic_tac_led = TicLedPin;
    }
  }

  // compare the current time to the previous time an LED turned on
  // if it is greater than your interval, run the if statement
  if (current_time - previous_time > interval) {
    // save the current time as the last time you changed an LED
    previous_time = current_time;
    // Turn the LED on
    digitalWrite(led, HIGH);
    // increment the led variable
    // in 10 minutes the next LED will light up
    led++;

    // Tone when 10 sec is up
    if (led != 8) {
      tone(PiezzoPin, NoteSec, 100);
    }

    if (led == 8) {
      // the min is up
      tone(PiezzoPin, NoteMin, 100);
      delay(400);

      resetPins();
    }
  }

  // read the switch value
  switch_state = digitalRead(SwitchPin);

  // if the switch has changed
  if (switch_state != prev_switch_state) {
    resetPins();

    //reset the timer
    previous_time = current_time;
  }
  // set the previous switch state to the current state
  prev_switch_state = switch_state;
}

void resetPins() {
     // turn all the LEDs low
    for (int i = 2; i < 8; i++) {
      digitalWrite(i, LOW);
    }

    // reset the LED variable to the first one
    led = 2;
}
