#include <LiquidCrystal.h>
#include "MenuLCD.h"
#include "MenuEntry.h"
#include "MenuIntHelper.h"
#include "MenuManager.h"
#include "AccelStepper.h"


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

void setupMenus()
{
  g_menuLCD.MenuLCDSetup();
  
  MenuEntry * p_menuEntryRoot;
  p_menuEntryRoot = new MenuEntry("Setup", NULL, NULL);
  g_menuManager.addMenuRoot( p_menuEntryRoot );
  g_menuManager.addChild( new MenuEntry("Max Pan Left", NULL, setMaxPanLeftCallback));
  g_menuManager.addChild( new MenuEntry("Max Pan Right", NULL, setMaxPanRightCallback));
//  g_menuManager.addChild( new MenuEntry("Max Tilt Up", NULL, setMaxTiltUpCallback));
//  g_menuManager.addChild( new MenuEntry("Max Tilt Down", NULL, setMaxTiltDownCallback));
  g_menuManager.addChild( new MenuEntry("Pan Step", NULL, setPanStepCallback));
  g_menuManager.addChild( new MenuEntry("Take Picture", NULL, takePictureCallback));
//  g_menuManager.addChild( new MenuEntry("Tilt Step", NULL, setMaxTiltStepCallback));
  
  g_menuManager.addChild( new MenuEntry("Back", (void*) &g_menuManager, MenuEntry_BackCallbackFunc));
  g_menuManager.addSibling( new MenuEntry("Run Scan", NULL, runScanCallback));
  g_menuManager.addSibling( new MenuEntry("Credits", NULL, NULL));
  g_menuManager.DrawMenu();
}

AccelStepper panStepper(AccelStepper::DRIVER, PAN_STEP_PIN, PAN_DIR_PIN);
AccelStepper tiltStepper(AccelStepper::DRIVER, TILT_STEP_PIN, TILT_DIR_PIN);

void setup() 
{
  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);  
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  panStepper.setMaxSpeed(200.0);
  panStepper.setAcceleration(200.0);
  panStepper.setPinsInverted(true,false,false);
  setupMenus();
}

boolean g_runScan = false;
boolean g_isMaxPanLeftSetup = false;
boolean g_isMaxPanRightSetup = false;
boolean g_isPanStepSetup = false;
boolean g_runScanRight = false;
boolean g_takePicture = false;
 
int pan_step_per_deg = 7;
int g_maxPanLeftDeg = -10;
int g_maxPanRightDeg = +10;
int g_panStepDeg = 0;
int g_scanCurrentPanPosition = 0;

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
  g_menuManager.DoMenuAction( MENU_ACTION_SELECT);
  break;
}
case KEYPAD_NONE:
{
break;
}
} //switch-case Befehl beenden
  if (g_runScan) {
    if (panStepper.distanceToGo() == 0)
    {
      if (g_takePicture) {
        triggerPicture();
      } else {
        if (g_runScanRight) {
          g_scanCurrentPanPosition = g_scanCurrentPanPosition + g_panStepDeg;
          if (g_scanCurrentPanPosition > g_maxPanRightDeg)
            g_runScanRight = false;
        } else {
          g_scanCurrentPanPosition = g_scanCurrentPanPosition - g_panStepDeg;        
          if (g_scanCurrentPanPosition < g_maxPanLeftDeg)
            g_runScanRight = true;
        }
        panStepper.moveTo(g_scanCurrentPanPosition * pan_step_per_deg);
        g_takePicture = true;
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
  panStepper.run();
} //Loop beenden

int triggerPicture() 
{
//  if (TRIGGER_PICTURE_STATE == START) 
//  {
//  }
//  digitalWrite(FOCUS_PIN, HIGH);
//  delay(1000);
  digitalWrite(SHUTTER_PIN, HIGH);
  delay(1250);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  g_takePicture = false;
}

void runScanCallback( char* pMenuText, void*pUserData)
{
  g_runScan = true;
  g_runScanRight = true;
  g_takePicture = true;
  g_scanCurrentPanPosition = g_maxPanLeftDeg;
  panStepper.moveTo(g_maxPanLeftDeg * pan_step_per_deg);
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

void setPanStepCallback( char* pMenuText, void*pUserData)
{
  char *pLabel = "Pan Step";
  g_isPanStepSetup = true;
  g_menuManager.DoIntInput( 0, 90, g_panStepDeg, 1, &pLabel, 1, &g_panStepDeg);  
}

void takePictureCallback( char* pMenuText, void*pUserData)
{
  triggerPicture();  
}
