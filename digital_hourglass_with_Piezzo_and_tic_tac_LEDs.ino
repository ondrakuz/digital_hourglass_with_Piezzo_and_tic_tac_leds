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

  Created 25.03.2026
  by Ondřej Kužel  
*/

// named constant for the switch pin
const int SwitchPin = 8;
const int TicLedPin = 10;
const int TacLedPin = 11;

const int PiezzoPin = 9;

const int NumOfLeds = 6;

// frekvences of tones
const int NoteSec = 262;
const int NoteMin = 349;


// variables
unsigned long previousTime = 0;  // store the last time an LED was updated
unsigned long previousTicTime = 0; // store the last time of switching of an tic-tac LEDs

int switchState = 0;             // the current switch state
int prevSwitchState = 0;         // the previous switch state
int ticTacLedPin = 10;           // the switched on tic-tac LED (pin)
int led = 2;                     // a variable to refer to the LEDs

// 10000 = 10 seconds in milliseconds
unsigned long interval = 10000;  // interval at which to light the next LED = 10 sec
unsigned long ticTacInterval = 250; // interval at which switch the tic-tac LEDs on/off

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
  unsigned long currentTime = millis();

  // Tic Tac Leds
  if (currentTime - previousTicTime > ticTacInterval) {
    previousTicTime = currentTime;
    if (ticTacLedPin == TicLedPin) {
      digitalWrite(TicLedPin, LOW);
      digitalWrite(TacLedPin, HIGH);
      ticTacLedPin = TacLedPin;
    } else if (ticTacLedPin == TacLedPin) {
      digitalWrite(TacLedPin, LOW);
      digitalWrite(TicLedPin, HIGH);
      ticTacLedPin = TicLedPin;
    }
  }

  // compare the current time to the previous time an LED turned on
  // if it is greater than your interval, run the if statement
  if (currentTime - previousTime > interval) {
    // save the current time as the last time you changed an LED
    previousTime = currentTime;
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

      for (int i = 0; i < NumOfLeds; i++)
      {
        digitalWrite(i + 2, LOW);
      }
      led = 2;
    }
  }

  // read the switch value
  switchState = digitalRead(SwitchPin);

  // if the switch has changed
  if (switchState != prevSwitchState) {
    // turn all the LEDs low
    for (int x = 2; x < 8; x++) {
      digitalWrite(x, LOW);
    }

    // reset the LED variable to the first one
    led = 2;

    //reset the timer
    previousTime = currentTime;
  }
  // set the previous switch state to the current state
  prevSwitchState = switchState;
}
