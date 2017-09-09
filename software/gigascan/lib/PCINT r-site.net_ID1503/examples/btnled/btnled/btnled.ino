#include <Arduino.h>

#include <pcint.h>

#define led 13
#define btn 12

void setled() {digitalWrite(led,digitalRead(btn));}

void setup() {
  pinMode(led,OUTPUT);
  pinMode(btn,INPUT_PULLUP);
  PCattachInterrupt<btn>(setled,CHANGE);
  setled();//initial led status
}

void loop() {}
