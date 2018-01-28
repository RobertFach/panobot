/* Copyright (C) 2017 Robert Fach All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Robert Fach
e-mail   :  robert.fach@gmx.net
*/

#include <Arduino.h>
#include <Streaming.h>

#ifdef ESP8266
  #define typeof(x) __typeof__(x)
  #include <SPI.h>
  #include <Wire.h>
#endif

#include <config.h>
#include <eeprom-config.h>

#include <AccelStepper.h>
#include <math.h>

#include <menu.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialOut.h>
#include <menuIO/u8g2Out.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>

using namespace Menu;

//panobot logic & motor control
AccelStepper panStepper(AccelStepper::DRIVER, PAN_STEP_PIN, PAN_DIR_PIN);
AccelStepper tiltStepper(AccelStepper::DRIVER, TILT_STEP_PIN, TILT_DIR_PIN);

boolean g_runScan = false;
boolean g_isMaxPanLeftSetup = false;
boolean g_isMaxPanRightSetup = false;
boolean g_isPanStepSetup = false;
boolean g_isMaxTiltUpSetup = false;
boolean g_isMaxTiltDownSetup = false;
boolean g_isTiltStepSetup = false;
boolean g_updateStatus = true;

double g_panStepDeg = 0;
double g_tiltStepDeg = 0;
int g_scanPositionHorizontal = 0;
int g_scanPositionVertical = 0;
int g_picturesHorizontal = 0;
int g_picturesVertical = 0;
int g_picturesCount = 0;
int g_picturesTotal = 0;
double panPos = 0;
double tiltPos = 0;

double g_sensorFF_horizontal = 36.0;
double g_sensorFF_vertical = 24.0;
double g_hfov = 0;
double g_vfov = 0;


//callback function used by the menu to do the math when updating some values
void updateScanner() {
  g_hfov = degrees( 2 * atan2(g_sensorFF_horizontal, user_config.crop_factor * 2 * user_config.focal_length));
  g_vfov = degrees( 2 * atan2(g_sensorFF_vertical, user_config.crop_factor * 2 * user_config.focal_length));
  g_panStepDeg = g_hfov * (100 - user_config.horizontal_overlap) / 100;
  g_tiltStepDeg = g_vfov * (100 - user_config.vertical_overlap) / 100;
  g_picturesHorizontal = ceil((abs(user_config.scan_max_pan_left) + abs(user_config.scan_max_pan_right)) / g_panStepDeg);
  g_picturesVertical = ceil((abs(user_config.scan_max_tilt_up) + abs(user_config.scan_max_tilt_down)) / g_tiltStepDeg);
  g_picturesTotal = g_picturesHorizontal * g_picturesVertical;
  Serial.print("HSCAN: "); Serial.println(abs(user_config.scan_max_pan_left) + abs(user_config.scan_max_pan_right), DEC);
  Serial.print("VSCAN: "); Serial.println(abs(user_config.scan_max_tilt_up) + abs(user_config.scan_max_tilt_down), DEC);
  Serial.print("g_hfov: "); Serial.println(g_hfov,DEC);
  Serial.print("g_vfov: "); Serial.println(g_vfov,DEC);
  Serial.print("g_panStepDeg: "); Serial.println(user_config.pan_steps_per_degree,DEC);
  Serial.print("g_tiltStepDeg: "); Serial.println(user_config.tilt_steps_per_degree,DEC);
  Serial.print("g_picturesHorizontal: "); Serial.println(g_picturesHorizontal, DEC);
  Serial.print("g_picturesVertical: "); Serial.println(g_picturesVertical, DEC);
  Serial.print("g_picturesTotal: "); Serial.println(g_picturesTotal, DEC);
  //g_updateStatus = true;
}

void updateMaxPanLeftPosition(eventMask e) {
  if (e & exitEvent) {
    panStepper.moveTo(0);
  } else {
    panStepper.moveTo(user_config.scan_max_pan_left * user_config.pan_steps_per_degree);
  }
  updateScanner();
}
void updateMaxPanRightPosition(eventMask e) {
  if (e & exitEvent) {
    panStepper.moveTo(0);
  } else {
    panStepper.moveTo(user_config.scan_max_pan_right * user_config.pan_steps_per_degree);
  }
  updateScanner();
}

void updateMaxTiltUpPosition(eventMask e) {
  if (e & exitEvent) {
    tiltStepper.moveTo(0);
  } else {
    tiltStepper.moveTo(user_config.scan_max_tilt_up * user_config.tilt_steps_per_degree);
  }
  updateScanner();
}

void updateMaxTiltDownPosition(eventMask e) {
  if (e & exitEvent) {
    tiltStepper.moveTo(0);
  } else {
    tiltStepper.moveTo(user_config.scan_max_tilt_down * user_config.tilt_steps_per_degree);
  }
  updateScanner();
}

void printScannerStats() {
  Serial.print("H[");
  Serial.print(g_scanPositionHorizontal+1, DEC);
  Serial.print("/");
  Serial.print(g_picturesHorizontal, DEC);
  Serial.println("]");
  Serial.print("V[");
  Serial.print(g_scanPositionVertical+1, DEC);
  Serial.print("/");
  Serial.print(g_picturesVertical, DEC);
  Serial.println("]");
  Serial.print("T[");
  Serial.print(g_picturesCount, DEC);
  Serial.print("/");
  Serial.print(g_picturesTotal, DEC);
  Serial.println("]");
}

typedef enum {
  IDLE,
  POSITIONING,
  STABILIZE_WAIT,
  FOCUS_WAIT,
  TRIGGER_WAIT,
  FINISH
} eSystemState;

typedef enum {
  ZICK_ZACK_LEFT_RIGHT_DOWN_UP,
  SPHERICAL
} eSystemModePattern;

eSystemState state = IDLE;
eSystemModePattern modePattern = ZICK_ZACK_LEFT_RIGHT_DOWN_UP;
long delayTime = 0;
long startTime = 0;

void runScanCallback()
{
  g_runScan = true;
  g_scanPositionHorizontal = 0;
  g_scanPositionVertical = 0;
  g_updateStatus = true;
  modePattern = ZICK_ZACK_LEFT_RIGHT_DOWN_UP;
}

void runSphereCallback()
{
  g_runScan = true;
  modePattern = SPHERICAL;
  g_picturesTotal = 0;
}

eSystemState updatePosition(eSystemState state, eSystemModePattern mode) {
   if (state == IDLE) {
      if (mode == ZICK_ZACK_LEFT_RIGHT_DOWN_UP) {
        g_updateStatus = true;
        panPos = user_config.scan_max_pan_left;
        tiltPos = user_config.scan_max_tilt_down;
      } else if (mode == SPHERICAL) {
        panPos = 0;
        tiltPos = -60;
      }
   } else {
      if (mode == ZICK_ZACK_LEFT_RIGHT_DOWN_UP) {
        g_updateStatus = true;
        if (g_scanPositionHorizontal >= g_picturesHorizontal-1) {
          if (g_scanPositionVertical >= g_picturesVertical-1) {
            g_runScan = false;
            panPos = 0;
            tiltPos = 0;
            tiltStepper.moveTo(tiltPos * user_config.tilt_steps_per_degree);
            panStepper.moveTo(panPos * user_config.pan_steps_per_degree);
            return FINISH;
          } else {
            tiltPos += g_tiltStepDeg;
          }
          panPos = user_config.scan_max_pan_left;
          g_scanPositionHorizontal = 0;
          g_scanPositionVertical++;
        } else {
          panPos += g_panStepDeg;
          g_scanPositionHorizontal++;
        }
      } else if (mode == SPHERICAL) {

        if (panPos > 360 || tiltPos == 90) {
          if (tiltPos == 90) {
            g_runScan = false;
            panPos = 0;
            tiltPos = 0;
            tiltStepper.moveTo(tiltPos * user_config.tilt_steps_per_degree);
            panStepper.moveTo(panPos * user_config.pan_steps_per_degree);
            return FINISH;
          } else {
            tiltPos += g_tiltStepDeg;
            if (tiltPos > 90) {
              tiltPos = 90;
            }
          }
          panPos = 0;
          panStepper.setCurrentPosition(0);
        } else {
          if (tiltPos != 90) {
            panPos += abs(floor(g_panStepDeg * 1 / cos( radians(tiltPos))));
          }
        }
      }
   }
   tiltStepper.moveTo(tiltPos * user_config.tilt_steps_per_degree);
   panStepper.moveTo(panPos * user_config.pan_steps_per_degree);
   return POSITIONING;
}

void stateMachine() {
  if (state == IDLE && g_runScan) {
    state = updatePosition(state, modePattern);
  }
  if (state == POSITIONING) {
    if (tiltStepper.distanceToGo() == 0 && panStepper.distanceToGo() == 0) {
      delayTime = user_config.stabilize_and_write_delay;
      startTime = millis();
      state = STABILIZE_WAIT;
    }
  }
  if (state == STABILIZE_WAIT) {
    if (millis() - startTime > delayTime) {
      digitalWrite(FOCUS_PIN, HIGH);
      delayTime = user_config.focus_delay;
      startTime = millis();
      state = FOCUS_WAIT;
    }
  }
  if (state == FOCUS_WAIT) {
    if (millis() - startTime > delayTime) {
      digitalWrite(SHUTTER_PIN, HIGH);
      delayTime = user_config.trigger_delay;
      startTime = millis();
      state = TRIGGER_WAIT;
    }
  }
  if (state == TRIGGER_WAIT) {
    if (millis() - startTime > delayTime) {
      g_picturesCount++;
      g_updateStatus = true;
      printScannerStats();
      digitalWrite(FOCUS_PIN, LOW);
      digitalWrite(SHUTTER_PIN, LOW);
      state = updatePosition(state,modePattern);
    }
  }
  if (state == FINISH) {
    if (tiltStepper.distanceToGo() == 0 && panStepper.distanceToGo() == 0) {
      state = IDLE;
    }
  }
}

void initializeSteppers() {
  panStepper.setMaxSpeed(user_config.maximum_pan_speed);
  panStepper.setAcceleration(user_config.pan_acceleration);
  panStepper.setPinsInverted(true,false,false);
  tiltStepper.setMaxSpeed(user_config.maximum_tilt_speed);
  tiltStepper.setAcceleration(user_config.tilt_acceleration);
  tiltStepper.setPinsInverted(false,false,false);
}

//initializes everything which is bot related
void setupPanoBot() {
  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  initializeSteppers();
  updateScanner();
  g_updateStatus = true;
}

void resetConfiguration() {
  resetToDefaultConfig();
  updateScanner();
}

//Panobot MENU system, it uses ArduinoMenu library in combination with U8g2

// define menu colors --------------------------------------------------------
//each color is in the format:
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
// this is a monochromatic color table
const colorDef<uint8_t> colors[] MEMMODE={
  {{0,0},{0,1,1}},//bgColor
  {{1,1},{1,0,0}},//fgColor
  {{1,0},{1,0,0}},//valColor
  {{1,1},{1,0,0}},//unitColor
  {{0,1},{0,0,1}},//cursorColor
  {{0,0},{1,1,1}},//titleColor
};

#define fontName u8g2_font_5x7_tf
#define fontX 5
#define fontY 8
#define offsetX 5
#define offsetY 32
#define MAX_DEPTH 2

//initialize SmartLCD display, hardware SPI
U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, DISPLAY_CS_PIN, U8X8_PIN_NONE);

// Panobot Setup Menu
MENU(subMenuSetup,"Setup",doNothing,noEvent,noStyle
  ,FIELD(user_config.scan_max_pan_left,      "Pan Left     ","DEG",-200,0,10,1,updateMaxPanLeftPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(user_config.scan_max_pan_right,     "Pan Right    ","DEG",0,200,10,1,updateMaxPanRightPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(user_config.scan_max_tilt_up,       "Tilt UP      ","DEG",0,100,10,1,updateMaxTiltUpPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(user_config.scan_max_tilt_down,     "Tilt Down    ","DEG",-90,0,10,1,updateMaxTiltDownPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(user_config.stabilize_and_write_delay,"StWr Delay","ms",0,5000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(user_config.focus_delay,   "Focus Delay  ","ms",0,15000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(user_config.trigger_delay,       "Trigger Delay","ms",0,15000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(user_config.focal_length, "Focal Length ","mm",1,1000,10,1,updateScanner,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(user_config.horizontal_overlap, "Hor. Overlap ","%",0,100,10,1,updateScanner,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(user_config.vertical_overlap, "Ver. Overlap ","%",0,100,10,1,updateScanner,enterEvent | exitEvent| updateEvent,wrapStyle)
  ,FIELD(user_config.crop_factor, "Crop Factor  ","",0,10,0.1,0.01,updateScanner,enterEvent | exitEvent| updateEvent,wrapStyle)
  ,OP("Save", saveConfig, enterEvent)
  ,OP("Reset", resetConfiguration, enterEvent)
  ,EXIT("<Back")
);

MENU(subMenuHardware,"Hardware",doNothing,noEvent,noStyle
  ,FIELD(user_config.pan_steps_per_degree,  "PAN  ", "#/deg",0,1000,10,1, doNothing, noEvent, wrapStyle)
  ,FIELD(user_config.tilt_steps_per_degree, "TILT ", "#/deg",0,1000,10,1, doNothing, noEvent, wrapStyle)
  ,FIELD(user_config.maximum_pan_speed,     "Pan  Speed", "", 0, 5000, 100, 10, initializeSteppers, enterEvent | exitEvent| updateEvent, wrapStyle)
  ,FIELD(user_config.pan_acceleration,     "Pan  Accel", "", 0, 5000, 100, 10, initializeSteppers, enterEvent | exitEvent| updateEvent, wrapStyle)
  ,FIELD(user_config.maximum_tilt_speed,    "Tilt Speed", "", 0, 5000, 100, 10, initializeSteppers, enterEvent | exitEvent| updateEvent, wrapStyle)
  ,FIELD(user_config.tilt_acceleration,    "Tilt Accel", "", 0, 5000, 100, 10, initializeSteppers, enterEvent | exitEvent| updateEvent, wrapStyle)
  ,OP("Save", saveConfig, enterEvent)
  ,OP("Reset", resetConfiguration, enterEvent)
  ,EXIT("<Back")
)

//Panobot Main Menu
MENU(mainMenu,"Main menu",doNothing,noEvent,noStyle
  ,OP("Scan",runScanCallback,enterEvent)
  ,OP("Sphere", runSphereCallback,enterEvent)
  ,OP("Take Picture",doNothing,enterEvent)
  ,SUBMENU(subMenuSetup)
  ,SUBMENU(subMenuHardware)
);

//SmartLCD encoder driver
encoderIn<ENCODER_A_PIN,ENCODER_B_PIN> encoder;
encoderInStream<ENCODER_A_PIN,ENCODER_B_PIN> encStream(encoder,4);
//SmartLCD encoder key and reset button routed to the same "enter" command
keyMap encBtn_map[]={{ENCODER_BTN_PIN,options->getCmdChar(enterCmd)},{DISPLAY_RESET_BTN_PIN,options->getCmdChar(enterCmd)}};//negative pin numbers use internal pull-up, this is on when low
keyIn<2> encButton(encBtn_map);
//combine all streams as input streams
Stream* in[]={&encStream,&encButton,&Serial};
chainStream<3> sencoder(in);

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,(128-2*offsetX)/fontX,32/fontY})
  ,SERIAL_OUT(Serial)
);

NAVROOT(nav,mainMenu,MAX_DEPTH,sencoder,out);

config myOptions('*','-',false,false,defaultNavCodes);

//this function writes the Panobot status to the LCD
void drawStatus() {
  enum {BufSize=128/fontX};
  char buf1[BufSize];
  char buf2[BufSize];
  snprintf (buf1, BufSize, "H[%02d/%02d]V[%02d/%02d]",
  g_scanPositionHorizontal+1,
  g_picturesHorizontal,
  g_scanPositionVertical+1,
  g_picturesVertical
  );
  snprintf (buf2, BufSize, "T[%03d/%03d]",
  g_picturesCount,
  g_picturesTotal
  );
  u8g2.drawStr(128 - fontX * strlen(buf1), 8, buf1);
  u8g2.drawStr(128 - fontX * strlen(buf2), 16, buf2);
  g_updateStatus = false;
}

void splashscreen() {
  u8g2.clearBuffer();
  int x;
  int y;
  for (x=0;x<128;x++) {
    for (y=0;y<64;y++) {
      if (pgm_read_byte_near(SPLASHSCREEN + x*64+y) =='1')
        u8g2.drawPixel(x, y);
    }
  }
  u8g2.sendBuffer();
  delay(5000);
}

void setup() {
  loadConfig();
  options = &myOptions;
  //initialize Serial interface
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Panobot");Serial.flush();
  //initialize menu
  u8g2.begin();
  u8g2.setFont(fontName);
  encButton.begin();
  encoder.begin();
  //initialize bot
  setupPanoBot();
  splashscreen();
}

void loop() {
  nav.doInput();
  if (nav.changed(0) || g_updateStatus) {
    u8g2.clearBuffer();
    nav.doOutput();
    //this fixes?? an issue with ArduinoMenu, when the Cursor is over the last entry in a Menu,
    //the color mode/draw is set to XOR?? -> issue bug/question report
    u8g2.setFontMode(1);
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_ncenB12_tr);
    u8g2.drawStr(0, 32, "PANOBOT");
    u8g2.setFont(fontName);
    drawStatus();
    u8g2.sendBuffer();
  }
  stateMachine();
  panStepper.run();
  tiltStepper.run();
}
