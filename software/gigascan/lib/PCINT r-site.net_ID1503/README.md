# PCINT

## Pin Change Interrupt Library

[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](http://creativecommons.org/licenses/by-nc-sa/4.0/)
[![Build Status](https://travis-ci.org/neu-rah/PCINT.svg?branch=master)](https://travis-ci.org/neu-rah/PCINT)


Arduino pin change interrupt library compatible with AVR and SAM with consistent interface.

Allows handlers to be called with a predefined cargo (void*) for user data or just regular void returning functions with no params.

This library use meta-programing to achieve consistency.

If your board is not supported please see mkPCIntMap example.

Supporting 328, 2560 and due and including example sketch to obtain pin maps for other MCUs.

If you use the example to build maps for other AVR's please let me know (pull request) so that i can include them for benefit of other users. Thanks.

## Example

```c++
#include <pcint.h>

#define led 13
#define btn 12

void setled() {
  digitalWrite(led,digitalRead(btn));
}

void setup() {
  pinMode(led,OUTPUT);
  pinMode(btn,INPUT_PULLUP);
  PCattachInterrupt<btn>(setled,CHANGE);
  setled();//initial led status
}

void loop() {}
```

## API

### PCattachInterrupt

```c++
void PCattachInterrupt<pin>(userFunc,mode);
```
monitor pin and call user function on change.

- pin - your board pin number
- userFunc - function to be called on pin change
- mode - when to call the function, can be CHANGE | RISING | FALLING

### PCdetachInterrupt

```c++
void PCdetachInterrupt<pin>();
```

stop monitoring pin change on given pin.

- pin - your board pin number

## History

(Oct 2016) V4.0 changed API to support arduino due.

(Jul 2016) added skectch to print PCINT maps, please pull or send me new maps.
This allows you to add support for your board pinout definition.

(Nov.2014) using arduino PCINT macros for wider compatibility

(Sep.2014) Made this because i need a PCINT handler that can have extra data attached.
