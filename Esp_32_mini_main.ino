/*
  Debounce


  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).


  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached from pin 2 to +5V
  - 10 kilohm resistor attached from pin 2 to ground


  - Note: On most Arduino boards, there is already an LED on the board connected
    to pin 13, so you don't need any extra components for this example.


  created 21 Nov 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Limor Fried
  modified 28 Dec 2012
  by Mike Walters
  modified 30 Aug 2016
  by Arturo Guadalupi


  This example code is in the public domain.


  https://docs.arduino.cc/built-in-examples/digital/Debounce/
*/


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 35;  // the number of the pushbutton pin
const int redledPin = 32;    // the number of the blue LED pin
const int greenledPin = 33;    // the number of the blue LED pin
const int blueledPin = 25;    // the number of the blue LED pin
unsigned long previousMillis = 0;

// Variables will change:
int ledState = 0;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int blink_speed;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  pinMode(blueledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println(ledState);


  // set initial LED state
  all_on();
}


void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:


  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:


    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
      ledState += 1;
      if (ledState >=5) {
        ledState = 0;
        }
      if (ledState == 0) {
        all_on();
      }
      if (ledState == 1) {
        all_off();
      }
      if (ledState == 2) {
        left_on();
      }
      if (ledState == 3) {
        right_on();
      }
      if (ledState == 4) {
        blinking();
      }
      Serial.println(ledState);

      }
    }
  }

  Serial.println(blink_speed);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  if (ledState == 4) {
    blinking();
  }
  lastButtonState = reading;
}
void all_off() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, LOW);
}

void all_on() {
  digitalWrite(redledPin, HIGH);
  digitalWrite(greenledPin, HIGH);
  digitalWrite(blueledPin, HIGH);
}
void left_on() {
  digitalWrite(redledPin, HIGH);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, LOW);
}
void right_on() {
  digitalWrite(redledPin, LOW);
  digitalWrite(greenledPin, LOW);
  digitalWrite(blueledPin, HIGH);
}
void blinking() {
  unsigned long currentMillis = millis();
  int blink_speed = analogRead(34) / 2;

  if (currentMillis - previousMillis >= blink_speed) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (digitalRead(redledPin) == LOW) {
      all_on();
    } else {
      all_off();
    }
  }
}