#include <Arduino.h>
#include <Streaming.h>

/********************
Arduino generic menu system
U8G2 menu example
U8G2: https://github.com/olikraus/u8g2

Oct. 2016 Stephen Denne https://github.com/datacute
Based on example from Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
Original from: https://github.com/christophepersoz
creative commons license 3.0: Attribution-ShareAlike CC BY-SA
This software is furnished "as is", without technical support, and with no
warranty, express or implied, as to its usefulness for any purpose.

Thread Safe: No
Extensible: Yes

menu on U8G2 device
output: Wemos D1 mini OLED Shield (SSD1306 64x48 I2C) + Serial
input: Serial
platform: espressif8266

*/

#ifdef ESP8266
  #define typeof(x) __typeof__(x)
  #include <SPI.h>
  #include <Wire.h>
#endif

#include <config.h>

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
boolean g_runScanRight = false;
boolean g_takePicture = false;
boolean g_runTilt = false;

int pan_step_per_deg = 7 * 8;
int g_maxPanLeftDeg = -10;
int g_maxPanRightDeg = +10;
double g_panStepDeg = 0;
int tilt_step_per_deg = 35;
int g_maxTiltUpDeg = +10;
int g_maxTiltDownDeg = -10;
double g_tiltStepDeg = 0;
int g_scanPositionHorizontal = 0;
int g_scanPositionVertical = 0;
int g_picturesHorizontal = 0;
int g_picturesVertical = 0;
int g_picturesCount = 0;
int g_picturesTotal = 0;
int g_takePictureDelay = 250;
int g_takePicturePreDelay = 0;
int g_shutterDelay = 500;

double g_crop = 1.6;
double g_sensorFF_horizontal = 36.0;
double g_sensorFF_vertical = 24.0;
int g_focalLength = 300;
int g_hol = 30;
int g_vol = 30;
double g_hfov = 0;
double g_vfov = 0;

void updateScanner() {
  g_hfov = degrees( 2 * atan2(g_sensorFF_horizontal, g_crop * 2 * g_focalLength));
  g_vfov = degrees( 2 * atan2(g_sensorFF_vertical, g_crop * 2 * g_focalLength));
  g_panStepDeg = g_hfov * (100 - g_hol) / 100;
  g_tiltStepDeg = g_vfov * (100 - g_vol) / 100;
  g_picturesHorizontal = ceil((abs(g_maxPanLeftDeg) + abs(g_maxPanRightDeg)) / g_panStepDeg);
  g_picturesVertical = ceil((abs(g_maxTiltUpDeg) + abs(g_maxTiltDownDeg)) / g_tiltStepDeg);
  g_picturesTotal = g_picturesHorizontal * g_picturesVertical;
  Serial.print("HSCAN: "); Serial.println(abs(g_maxPanLeftDeg) + abs(g_maxPanRightDeg), DEC);
  Serial.print("VSCAN: "); Serial.println(abs(g_maxTiltUpDeg) + abs(g_maxTiltDownDeg), DEC);
  Serial.print("g_hfov: "); Serial.println(g_hfov,DEC);
  Serial.print("g_vfov: "); Serial.println(g_vfov,DEC);
  Serial.print("g_panStepDeg: "); Serial.println(g_panStepDeg,DEC);
  Serial.print("g_tiltStepDeg: "); Serial.println(g_tiltStepDeg,DEC);
  Serial.print("g_picturesHorizontal: "); Serial.println(g_picturesHorizontal, DEC);
  Serial.print("g_picturesVertical: "); Serial.println(g_picturesVertical, DEC);
  Serial.print("g_picturesTotal: "); Serial.println(g_picturesTotal, DEC);
}

void updateMaxPanLeftPosition(eventMask e) {
  if (e & exitEvent) {
    panStepper.moveTo(0);
  } else {
    panStepper.moveTo(g_maxPanLeftDeg * pan_step_per_deg);
  }
  updateScanner();
}
void updateMaxPanRightPosition(eventMask e) {
  if (e & exitEvent) {
    panStepper.moveTo(0);
  } else {
    panStepper.moveTo(g_maxPanRightDeg * pan_step_per_deg);
  }
  updateScanner();
}

void updateMaxTiltUpPosition(eventMask e) {
  if (e & exitEvent) {
    tiltStepper.moveTo(0);
  } else {
    tiltStepper.moveTo(g_maxTiltUpDeg * tilt_step_per_deg);
  }
  updateScanner();
}

void updateMaxTiltDownPosition(eventMask e) {
  if (e & exitEvent) {
    tiltStepper.moveTo(0);
  } else {
    tiltStepper.moveTo(g_maxTiltDownDeg * tilt_step_per_deg);
  }
  updateScanner();
}

void runScanCallback()
{
  g_runScan = true;
  g_runScanRight = true;
  g_runTilt = false;
  g_takePicture = true;
  g_scanPositionHorizontal = 0;
  g_scanPositionVertical = 0;
  panStepper.moveTo(g_maxPanLeftDeg * pan_step_per_deg);
  tiltStepper.moveTo(g_maxTiltDownDeg * tilt_step_per_deg);
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

void triggerPicture()
{
  digitalWrite(FOCUS_PIN, HIGH);
  delay(g_takePicturePreDelay);
  digitalWrite(SHUTTER_PIN, HIGH);
  delay(g_shutterDelay);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  delay(g_takePictureDelay);
  g_takePicture = false;
}

void runScanService() {
  if (g_runScan) {
    if (tiltStepper.distanceToGo() == 0)
      if (panStepper.distanceToGo() == 0)
      {
        printScannerStats();
        if (g_takePicture) {
          triggerPicture();
          g_picturesCount++;
        } else {
          g_takePicture = true;
          if (g_runTilt) {
              g_scanPositionVertical++;
              if (g_scanPositionVertical > g_picturesVertical-1) {
                g_runScan = false;
              } else {
                tiltStepper.move(g_tiltStepDeg * tilt_step_per_deg);
		            panStepper.moveTo(g_maxPanLeftDeg * pan_step_per_deg);
                g_runScanRight = true;
                g_runTilt = false;
              }
          } else if (g_runScanRight) {
            g_scanPositionHorizontal++;
            if (g_scanPositionHorizontal >= g_picturesHorizontal-1) {
              g_runScanRight = false;
	            g_scanPositionHorizontal = 0;
              g_runTilt = true;
            }
            panStepper.move(g_panStepDeg * pan_step_per_deg);
          }
        }
      }
  }
}

void setupPanoBot() {
  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  panStepper.setMaxSpeed(400.0);
  panStepper.setAcceleration(300.0);
  panStepper.setPinsInverted(true,false,false);
  tiltStepper.setMaxSpeed(400.0);
  tiltStepper.setAcceleration(300.0);
  tiltStepper.setPinsInverted(false,false,false);
}
//Menu stuff
U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, DISPLAY_CS_PIN, U8X8_PIN_NONE);

result zZz() {Serial.println("zZz");return proceed;}

result showEvent(eventMask e,navNode& nav,prompt& item) {
  Serial.print("event: ");
  Serial.println(e);
  return proceed;
}

// Panobot Setup Menu
MENU(subMenuSetup,"Setup",showEvent,anyEvent,noStyle
  ,FIELD(g_maxPanLeftDeg,      "Pan Left     ","DEG",-200,0,10,1,updateMaxPanLeftPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(g_maxPanRightDeg,     "Pan Right    ","DEG",0,200,10,1,updateMaxPanRightPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(g_maxTiltUpDeg,       "Tilt UP      ","DEG",0,100,10,1,updateMaxTiltUpPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(g_maxTiltDownDeg,     "Tilt Down    ","DEG",-90,0,10,1,updateMaxTiltDownPosition,enterEvent | exitEvent | updateEvent,wrapStyle)
  ,FIELD(g_takePicturePreDelay,"Image P-Delay","ms",0,5000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(g_takePictureDelay,   "Image Delay  ","ms",0,15000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(g_shutterDelay,       "Shutter Delay","ms",0,15000,1000,100,doNothing,noEvent,wrapStyle)
  ,FIELD(g_focalLength,        "Focal Length ","mm",1,1000,10,1,updateScanner,exitEvent,wrapStyle)
  ,FIELD(g_hol,                "Hor. Overlap ","%",0,100,10,1,updateScanner,exitEvent,wrapStyle)
  ,FIELD(g_vol,                "Ver. Overlap ","%",0,100,10,1,updateScanner,exitEvent,wrapStyle)
  ,EXIT("<Back")
);

MENU(mainMenu,"Main menu",zZz,noEvent,noStyle
  ,OP("Scan",runScanCallback,enterEvent)
  ,OP("Take Picture",triggerPicture,enterEvent)
  ,SUBMENU(subMenuSetup)
  ,EXIT("<Back")
);

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

encoderIn<ENCODER_A_PIN,ENCODER_B_PIN> encoder;//simple quad encoder driver
encoderInStream<ENCODER_A_PIN,ENCODER_B_PIN> encStream(encoder,4);// simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{ENCODER_BTN_PIN,options->getCmdChar(enterCmd)},{DISPLAY_RESET_BTN_PIN,options->getCmdChar(enterCmd)}};//negative pin numbers use internal pull-up, this is on when low
keyIn<2> encButton(encBtn_map);//1 is the number of keys

Stream* in[]={&encStream,&encButton,&Serial};
chainStream<3> sencoder(in);

#define fontName u8g2_font_5x7_tf
#define fontX 5
#define fontY 8
#define offsetX 12
#define offsetY 16
#define MAX_DEPTH 2

//this macro replaces all the above commented lines
MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,128/fontX,48/fontY})
  ,SERIAL_OUT(Serial)
);

NAVROOT(nav,mainMenu,MAX_DEPTH,sencoder,out);

//when menu is suspended
result idle(menuOut& o,idleEvent e) {
  o.clear();
  switch(e) {
    case idleStart:o.println("suspending menu!");break;
    case idling:o.println("suspended...");break;
    case idleEnd:o.println("resuming menu.");break;
  }
  return proceed;
}

config myOptions('*','-',false,false,defaultNavCodes);

void setup() {
  options = &myOptions;
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Panobot");Serial.flush();
  u8g2.begin();
  u8g2.setFont(fontName);

  nav.idleTask=idle;//point a function to be used when menu is suspended

  encButton.begin();
  encoder.begin();

  setupPanoBot();
}

void loop() {
  nav.doInput();
  if (nav.changed(0)) {//only draw if menu changed for gfx device
    //change checking leaves more time for other tasks
    u8g2.clearBuffer();
    u8g2.drawStr(0, 8, "PANOBOT");
    nav.doOutput();
    u8g2.sendBuffer();
  }
  runScanService();
  panStepper.run();
  tiltStepper.run();
}
