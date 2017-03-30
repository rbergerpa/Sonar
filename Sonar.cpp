#include "sonar.h"
#include <Arduino.h>

/*
 Driver library for LV-MaxSonar®_EZ sensors  from MaxBotix

    by Robert W. Berger
*/

static const int MICROSECONDS_PER_INCH = 147;
static const double MICROSECONDS_PER_FOOT = MICROSECONDS_PER_INCH * 12.0;

Sonar::Sonar(byte _pin) {
  pin = _pin;
  PciManager.registerListener(pin, this);
}

int Sonar::inches() {
  return duration / MICROSECONDS_PER_INCH;
};

float Sonar::feet() {
  return duration / MICROSECONDS_PER_FOOT;
}

void Sonar::pciHandleInterrupt(byte vector) {
  byte val = digitalRead(pin);

  // Mulitple pins share the same pin change interrupt vector, so we must check to see if the call is for this instance 
  if (val == prevVal) {
    return;
  }
  prevVal = val;

  if (val == HIGH) {
    startTime = micros();  // Start of pulse
  }  else {
    duration = micros() - startTime;  // End of pulse
  }
}

void startSonar(int pin) {
    // Output a pulse to start the daisy chained sync signals
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(4);
    digitalWrite(pin, LOW);
    delay(4);

    // Return the pin to high impedance to allow the round-robin daisy chaining
    pinMode(pin, INPUT);
}
