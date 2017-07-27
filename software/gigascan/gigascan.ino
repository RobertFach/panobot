#include <LiquidCrystal.h>
#include "MenuLCD.h"
#include "MenuEntry.h"
#include "MenuIntHelper.h"
#include "MenuManager.h"
#include <AccelStepper.h>
#include <math.h>

const int LCDRS = 8;
const int LCDE  = 9;
const int LCDD4 = 4;
const int LCDD5 = 5;
const int LCDD6 = 6;
const int LCDD7 = 7;

const int PAN_STEP_PIN  = 24;
const int PAN_DIR_PIN   = 25;
const int TILT_STEP_PIN = 26;
const int TILT_DIR_PIN = 27;
const int FOCUS_PIN    = 22;
const int SHUTTER_PIN  = 23;

MenuLCD g_menuLCD( LCDRS, LCDE, LCDD4, LCDD5, LCDD6, LCDD7, 16, 2);
MenuManager g_menuManager( &g_menuLCD);

// erstellen einiger Variablen
int Taster = 0;
int Analogwert = 0;
#define Tasterrechts 0
#define Tasteroben 1
#define Tasterunten 2
#define Tasterlinks 3
#define Tasterselect 4
#define KEYPAD_NONE 5
#define KEYPAD_BLOCKED 6

// Ab hier wird ein neuer Programmblock mit dem Namen "Tasterstatus" erstellt. Hier wird ausschließlich ausschließlich geprüft, welcher Taster gedrückt ist.
int Tasterstatus()
{
Analogwert = analogRead(A0); // Auslesen der Taster am Analogen Pin A0.
if (Analogwert > 1000) return KEYPAD_NONE;
if (Analogwert < 50) return Tasterrechts;
if (Analogwert < 195) return Tasteroben;
if (Analogwert < 380) return Tasterunten;
if (Analogwert < 555) return Tasterlinks;
if (Analogwert < 790) return Tasterselect;
 
return KEYPAD_NONE; // Ausgabe wenn kein Taster gedrückt wurde.
}

unsigned long _block_time = 0;
int _last_button;

int blockedButton() {
  // if we are still blocked, return this status
  if (millis() < _block_time)
    return KEYPAD_BLOCKED;

  uint8_t current = Tasterstatus();

  // if some key is pressed, disable presses for block_delay or repeat_delay if button is kept down
  if (current != KEYPAD_NONE)
    _block_time = millis() + (current == _last_button ? 500 : 500);

  _last_button = current;
  return current;  
}


// Menu Structure
// Setup
// |-Max Pan Left
// |-Max Pan Right
// |-Max Tilt Up
// |-Max Tilt Down
// |-Pan Step
// |-Tilt Step
// Run Scan
// Credits

void setMaxPanLeftCallback(char*, void*);
void setMaxPanRightCallback(char*, void*);
void setMaxTiltUpCallback(char*, void*);
void setMaxTiltDownCallback(char*, void*);
void setTakePicturePreDelayCallback(char*, void*);
void setTakePictureDelayCallback(char*, void*);
void setShutterDelayCallback(char*, void*);
void takePictureCallback(char*, void*);
void setFocalLength(char*, void*);
void setHOL(char*, void*);
void setVOL(char*, void*);
void runScanCallback(char*, void*);
int triggerPicture();

void setupMenus()
{
  g_menuLCD.MenuLCDSetup();
  
  MenuEntry * p_menuEntryRoot;
  p_menuEntryRoot = new MenuEntry("Setup", NULL, NULL);
  g_menuManager.addMenuRoot( p_menuEntryRoot );
  g_menuManager.addChild( new MenuEntry("Max Pan Left", NULL, setMaxPanLeftCallback));
  g_menuManager.addChild( new MenuEntry("Max Pan Right", NULL, setMaxPanRightCallback));
  g_menuManager.addChild( new MenuEntry("Max Tilt Up", NULL, setMaxTiltUpCallback));
  g_menuManager.addChild( new MenuEntry("Max Tilt Down", NULL, setMaxTiltDownCallback));
  g_menuManager.addChild( new MenuEntry("Image P-Delay", NULL, setTakePicturePreDelayCallback));
  g_menuManager.addChild( new MenuEntry("Image Delay", NULL, setTakePictureDelayCallback));
  g_menuManager.addChild( new MenuEntry("Shutter Delay", NULL, setShutterDelayCallback));
  g_menuManager.addChild( new MenuEntry("Take Image", NULL, takePictureCallback));
  g_menuManager.addChild( new MenuEntry("Focal Length", NULL, setFocalLength));
  g_menuManager.addChild( new MenuEntry("HOL", NULL, setHOL));
  g_menuManager.addChild( new MenuEntry("VOL", NULL, setVOL));
  
  g_menuManager.addChild( new MenuEntry("Back", (void*) &g_menuManager, MenuEntry_BackCallbackFunc));
  g_menuManager.addSibling( new MenuEntry("Run Scan", NULL, runScanCallback));
  g_menuManager.addSibling( new MenuEntry("Credits", NULL, NULL));
  g_menuManager.DrawMenu();
}

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
int tilt_step_per_deg = 7 * 8;
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
  g_panStepDeg = g_hfov * g_hol / 100;
  g_tiltStepDeg = g_vfov * g_vol / 100;
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

void setup() 
{
  Serial.begin(115200);
  Serial.println("Gigascan ready");
  
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
  setupMenus();
  updateScanner();
}



void loop()
{
Taster = blockedButton(); //Hier springt der Loop in den oben angegebenen Programmabschnitt "Tasterstatus" und liest dort den gedrückten Taster aus.

switch (Taster) // Abhängig von der gedrückten Taste wird in dem folgenden switch-case Befehl entschieden, was auf dem LCD angezeigt wird.
{
case Tasterrechts: // Wenn die rechte Taste gedrückt wurde...
{
  break;
}
case Tasterlinks:  // Wenn die linke Taste gedrückt wurde...
{
  g_menuManager.DoMenuAction( MENU_ACTION_BACK);
  break;
}
case Tasteroben:
{
  g_menuManager.DoMenuAction( MENU_ACTION_UP);
  break;
}
case Tasterunten:
{
  g_menuManager.DoMenuAction( MENU_ACTION_DOWN);
  break;
}
case Tasterselect:
{
  if (g_isMaxPanLeftSetup || g_isMaxPanRightSetup) {
    panStepper.moveTo(0);
    g_isMaxPanLeftSetup  = false;
    g_isMaxPanRightSetup = false;
  }
  if (g_isPanStepSetup) {
    panStepper.moveTo(0);
    g_isPanStepSetup = false;
  }
  if (g_isMaxTiltDownSetup || g_isMaxTiltUpSetup)
  {
    tiltStepper.moveTo(0);
    g_isMaxTiltDownSetup = false;
    g_isMaxTiltUpSetup = false;
  }
  if (g_isTiltStepSetup) {
    tiltStepper.moveTo(0);
    g_isTiltStepSetup = false;
  }  
  g_menuManager.DoMenuAction( MENU_ACTION_SELECT);
  updateScanner();
  break;
}
case KEYPAD_NONE:
{
break;
}
} //switch-case Befehl beenden
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
                
                g_runTilt = false;
              }
          } else if (g_runScanRight) {
            g_scanPositionHorizontal++;
            if (g_scanPositionHorizontal >= g_picturesHorizontal-1) {
              g_runScanRight = false;
              g_runTilt = true;
            }
            panStepper.move(g_panStepDeg * pan_step_per_deg);
          } else {
            g_scanPositionHorizontal--;        
            if (g_scanPositionHorizontal <= 0) {
              g_runScanRight = true;
              g_runTilt = true;
            }
            panStepper.move(-g_panStepDeg * pan_step_per_deg);
          }
          //g_takePicture = true;
        }
      }
  }
  if (g_isMaxPanLeftSetup) {
     panStepper.moveTo(g_maxPanLeftDeg * pan_step_per_deg);
  }
  if (g_isMaxPanRightSetup) {
     panStepper.moveTo(g_maxPanRightDeg * pan_step_per_deg);
  }
  if (g_isPanStepSetup) {
    panStepper.moveTo(g_panStepDeg * pan_step_per_deg);
  }
  if (g_isMaxTiltUpSetup) {
     tiltStepper.moveTo(g_maxTiltUpDeg * tilt_step_per_deg);
  }
  if (g_isMaxTiltDownSetup) {
     tiltStepper.moveTo(g_maxTiltDownDeg * tilt_step_per_deg);
  }
  if (g_isTiltStepSetup) {
    tiltStepper.moveTo(g_tiltStepDeg * tilt_step_per_deg);
  }
  panStepper.run();
  tiltStepper.run();
} //Loop beenden

int triggerPicture() 
{
//  if (TRIGGER_PICTURE_STATE == START) 
//  {
//  }
  digitalWrite(FOCUS_PIN, HIGH);
  delay(g_takePicturePreDelay);
  digitalWrite(SHUTTER_PIN, HIGH);
  delay(g_shutterDelay);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  delay(g_takePictureDelay);
  g_takePicture = false;
}

void runScanCallback( char* pMenuText, void*pUserData)
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

void setMaxPanLeftCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "max Pan Left";
  g_isMaxPanLeftSetup = true;
  g_menuManager.DoIntInput( -90, 0, g_maxPanLeftDeg, 1, &pLabel, 1, &g_maxPanLeftDeg);
}

void setMaxPanRightCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "max Pan Right";
  g_isMaxPanRightSetup = true;
  g_menuManager.DoIntInput( 0, 90, g_maxPanRightDeg, 1, &pLabel, 1, &g_maxPanRightDeg);
}

void setMaxTiltUpCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "max Tilt Up";
  g_isMaxTiltUpSetup = true;
  g_menuManager.DoIntInput( 0, 90, g_maxTiltUpDeg, 1, &pLabel, 1, &g_maxTiltUpDeg);
}

void setMaxTiltDownCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "max Tilt Down";
  g_isMaxTiltDownSetup = true;
  g_menuManager.DoIntInput( -90, 0, g_maxTiltDownDeg, 1, &pLabel, 1, &g_maxTiltDownDeg);
}

void setFocalLength( char* pMenuText, void*pUserData)
{
  char *pLabel = "Focal Length";
  g_menuManager.DoIntInput( 1, 600, g_focalLength, 10, &pLabel, 1, &g_focalLength);
}

void setHOL( char* pMenuText, void*pUserData)
{
  char *pLabel = "HOL";
  g_menuManager.DoIntInput( 1, 99, g_hol, 1, &pLabel, 1, &g_hol);
}

void setVOL( char* pMenuText, void*pUserData)
{
  char *pLabel = "VOL";
  g_menuManager.DoIntInput( 1, 99, g_vol, 1, &pLabel, 1, &g_vol);
}

void setTakePicturePreDelayCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "Image P-Delay";
  g_menuManager.DoIntInput( 0, 5000, g_takePicturePreDelay, 100, &pLabel, 1, &g_takePicturePreDelay);    
}

void setTakePictureDelayCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "Image Delay";
  g_menuManager.DoIntInput( 0, 150000, g_takePictureDelay, 500, &pLabel, 1, &g_takePictureDelay);    
}

void setShutterDelayCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "Shutter Delay";
  g_menuManager.DoIntInput( 0, 150000, g_shutterDelay, 1000, &pLabel, 1, &g_shutterDelay);    
}

void takePictureCallback( char* pMenuText, void*pUserData)
{
  triggerPicture();  
}
